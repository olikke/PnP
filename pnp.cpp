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
    clearMatrix();
}

void PnP::openMatrix(QString url)
{
    cv::FileStorage fs(QUrl(url).toLocalFile().toLatin1().constData(), cv::FileStorage::READ);
    if(!fs.isOpened()){
        qDebug()<<"Не удаётся открыть файл";
        cameraMatrix=cv::Mat::zeros(cameraMatrix.rows,cameraMatrix.cols,cameraMatrix.type());
        cameraModel->update();
        distMatrix=cv::Mat::zeros(distMatrix.rows,distMatrix.cols,distMatrix.type());
        distModel->update();
        return;
    }
    fs["DistorsionMatrix"]>>distMatrix;
    fs["CameraMatrix"]>>cameraMatrix;
    cameraModel->update();
    distModel->update();
}

void PnP::openImage(QString url)
{
    image=cv::imread(QUrl(url).toLocalFile().toLatin1().constData());
    emit newFrame(image);
    findChessboardCorners();
    clearMatrix();
}

void PnP::findPoint(QPointF point)
{
    double distance=1000.;
    int numb=-1;
    for (int i=0; i<corners.total();i++) {
        cv::Vec2f corner=corners.at<cv::Vec2f>(i);
        double d=qPow(corner[0]-point.x(),2)+qPow(corner[1]-point.y(),2);
        if (d<distance) {
            distance=d;
            numb=i;
        }
    }
    if (numb<0) return;
    cv::circle(image,cv::Point(corners.at<cv::Vec2f>(numb)),5, CV_RGB(255,0,0), 1, CV_AA, 0);
    emit newFrame(image);
    imgPoints.at<double>(0,m_pointNumb)=static_cast<double>(corners.at<cv::Vec2f>(numb)[0]);
    imgPoints.at<double>(1,m_pointNumb)=static_cast<double>(corners.at<cv::Vec2f>(numb)[1]);
    imgModel->update();
}

void PnP::setRadius(int val)
{
    m_radius=val;
    emit radiusChanged(val);
}

void PnP::setPointNumb(int numb)
{
   if (numb<0 || numb>distMatrix.cols-1) return;
   m_pointNumb=numb;
   emit pointNumbChanged(numb);
   imgModel->highlightColumn(m_pointNumb);
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
    qDebug()<<corners.type()<<CV_32FC2<<corners.total()<<corners.step;
}

void PnP::clearMatrix()
{
    imgPoints=cv::Mat::zeros(imgPoints.rows,imgPoints.cols,imgPoints.type());
    imgModel->update();
    objPoints=cv::Mat::zeros(objPoints.rows,objPoints.cols,objPoints.type());
    objModel->update();
    imgModel->highlightColumn(m_pointNumb);
}
