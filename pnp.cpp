#include "pnp.h"

PnP::PnP(AppConfigMini* appConfig,QObject *parent) :
    QObject(parent),
    m_appConfig(appConfig),
    cameraMatrix(cv::Mat(3,3,CV_64FC1)),
    distMatrix(cv::Mat(1,5,CV_64FC1)),
    imgPoints(cv::Mat(2,5,CV_64FC1)),
    objPoints(cv::Mat(3,5,CV_64FC1)),
    cameraModel(new MatModel(&cameraMatrix,this)),
    distModel(new MatModel(&distMatrix,this)),
    imgModel(new MatModel(&imgPoints,this)),
    objModel(new MatModel(&objPoints,this))
{
    imgPoints=cv::Mat::zeros(imgPoints.rows,imgPoints.cols,imgPoints.type());
    imgModel->update();
    clearCameraMatrix();
    clearImgMatrix();
    m_radius=appConfig->getSquareSize();
    calcObjPoint();
}

void PnP::openMatrix(QString url)
{
    cv::FileStorage fs(QUrl(url).toLocalFile().toLatin1().constData(), cv::FileStorage::READ);
    if(!fs.isOpened()){
        qDebug()<<"Не удаётся открыть файл";
        clearCameraMatrix();
        m_ready=false;
        emit readyChanged();
        return;
    }
    fs["DistorsionMatrix"]>>distMatrix;
    fs["CameraMatrix"]>>cameraMatrix;
    cameraModel->update();
    distModel->update();
    m_ready=true;
    emit readyChanged();
}

void PnP::openImage(QString url)
{
    image=cv::imread(QUrl(url).toLocalFile().toLatin1().constData());
    emit newFrame(image);
    findChessboardCorners();
    clearImgMatrix();
}

void PnP::findPoint(QPointF point)
{
    double distance=1000.;
    int numb=-1;
    for (int i=0; i<static_cast<int>(corners.total());i++) {
        cv::Vec2f corner=corners.at<cv::Vec2f>(i);
        double d=qPow(corner[0]-point.x(),2)+qPow(corner[1]-point.y(),2);
        if (d<distance) {
            distance=d;
            numb=i;
        }
    }
    if (numb<0) {
        emit clearTarget(m_pointNumb);
        return;
    }
    imgPoints.at<double>(0,m_pointNumb)=static_cast<double>(corners.at<cv::Vec2f>(numb)[0]);
    imgPoints.at<double>(1,m_pointNumb)=static_cast<double>(corners.at<cv::Vec2f>(numb)[1]);    
    emit paintTarget(m_pointNumb,QPointF(imgPoints.at<double>(0,m_pointNumb),
                                         imgPoints.at<double>(1,m_pointNumb)));
    imgModel->update();
}

void PnP::setPointNumb(int numb)
{
   if (numb<0 || numb>distMatrix.cols-1) return;
   m_pointNumb=numb;
   emit pointNumbChanged(numb);
   imgModel->highlightColumn(m_pointNumb);
}

void PnP::changePointNumb(bool incNumb)
{
    int v= incNumb?
               m_pointNumb==distMatrix.cols-1? 0: m_pointNumb+1:
               m_pointNumb==0? distMatrix.cols-1 : m_pointNumb-1;
    setPointNumb(v);
}

void PnP::start()
{
    cv::Mat rotation;
    cv::Mat translation;
    std::vector<cv::Point3d> objVector;
    for (int i=0; i<objPoints.cols; i++) {
        objVector.push_back(cv::Point3d(objPoints.at<double>(0,i),objPoints.at<double>(1,i),objPoints.at<double>(2,i)));
    }
    std::vector<cv::Point2f>imgVector;
    for (int i=0; i<imgPoints.cols; i++)
        imgVector.push_back(cv::Point2d(imgPoints.at<double>(0,i),imgPoints.at<double>(1,i)));
    if (!cv::solvePnP(objVector,imgVector,cameraMatrix,distMatrix,rotation,translation)) return;
    std::cout << "solvePNP Rotation Vector: " << rotation << std::endl;
    std::cout << "solvePNP TranslationVector: " << translation << std::endl;
    cv::Mat rotationMatrix;
    cv::Rodrigues(rotation,rotationMatrix);
    std::cout<<"Rotation Matrix: "<<rotationMatrix<<std::endl;
}

void PnP::squareSizeChanged(int value)
{
    m_radius=value;
    calcObjPoint();
}

void PnP::findChessboardCorners()
{
    cv::Mat temp;
    cv::cvtColor(image,temp,CV_BGR2GRAY);
    cv::Size m_boardSize=cv::Size(m_appConfig->getBorderWidth(),m_appConfig->getBoderHeight());
    bool success=cv::findChessboardCorners(temp,m_boardSize,corners);
    if (success) {
        cv::TermCriteria criteria=cv::TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,m_appConfig->getIterations(),m_appConfig->getEpsilon());
        cv::cornerSubPix(temp,corners,cv::Size(11,11),cv::Size(-1,-1),criteria);
    }
}

void PnP::clearImgMatrix()
{
    imgPoints=cv::Mat::zeros(imgPoints.rows,imgPoints.cols,imgPoints.type());
    imgModel->update();
    imgModel->highlightColumn(m_pointNumb);
    emit clearAll();
}

void PnP::calcObjPoint()
{
    //z - always 0
    objPoints=cv::Mat::zeros(objPoints.rows,objPoints.cols,objPoints.type());
    //central point
    objPoints.at<double>(0,0)=0.;
    objPoints.at<double>(1,0)=0.;
    //left point
    objPoints.at<double>(0,1)=-m_radius*1.;
    objPoints.at<double>(1,1)=0.;
    //up point
    objPoints.at<double>(0,2)=0;
    objPoints.at<double>(1,2)=-m_radius*1.;
    //right point
    objPoints.at<double>(0,3)=m_radius*1.;
    objPoints.at<double>(1,3)=0.;
    //down point
    objPoints.at<double>(0,4)=0;
    objPoints.at<double>(1,4)=m_radius*1.;
    objModel->update();
}

void PnP::clearCameraMatrix()
{
    cameraMatrix=cv::Mat::zeros(cameraMatrix.rows,cameraMatrix.cols,cameraMatrix.type());
    cameraModel->update();
    distMatrix=cv::Mat::zeros(distMatrix.rows,distMatrix.cols,distMatrix.type());
    distModel->update();
}
