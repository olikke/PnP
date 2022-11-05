#include "pnp.h"

PnP::PnP(AppConfigMini* appConfig,QObject *parent) :
    QObject(parent),
    m_appConfig(appConfig),
    cameraMatrix(cv::Mat(3,3,CV_64FC1)),
    distMatrix(cv::Mat(1,5,CV_64FC1)),
    imgPoints(cv::Mat(2,5,CV_64FC1)),
    objPoints(cv::Mat(3,5,CV_64FC1)),
    rotation(cv::Mat(1,3,CV_64FC1)),
    translation(cv::Mat(1,3,CV_64FC1)),
    cameraModel(new MatModel(&cameraMatrix,this)),
    distModel(new MatModel(&distMatrix,this)),
    imgModel(new MatModel(&imgPoints,this)),
    objModel(new MatModel(&objPoints,this)),
    rotModel(new MatModel(&rotation,this)),
    transModel(new MatModel(&translation,this))
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
    //cv::Mat rotation;
   // cv::Mat translation;
    std::vector<cv::Point3d> objVector;
    for (int i=0; i<objPoints.cols; i++) {
        objVector.push_back(cv::Point3d(objPoints.at<double>(0,i),objPoints.at<double>(1,i),objPoints.at<double>(2,i)));
    }
    std::vector<cv::Point2f>imgVector;
    for (int i=0; i<imgPoints.cols; i++)
        imgVector.push_back(cv::Point2d(imgPoints.at<double>(0,i),imgPoints.at<double>(1,i)));
    if (!cv::solvePnP(objVector,imgVector,cameraMatrix,distMatrix,rotation,translation)) {
        m_pnpReady=false;
        emit pnpReadyChanged();
        return;
    }
    qDebug()<<rotation.type()<<translation.type()<<cameraMatrix.type();
    std::cout << "solvePNP Rotation Vector: " << rotation << std::endl;
    std::cout << "solvePNP TranslationVector: " << translation << std::endl;
    cv::Mat rotationMatrix;
    cv::Rodrigues(rotation,rotationMatrix);
    std::cout<<"Rotation Matrix: "<<rotationMatrix<<std::endl;
    rotModel->update();
    transModel->update();
    m_pnpReady=true;
    emit pnpReadyChanged();
}

void PnP::antiRotate()
{
    int width=image.cols;
    int height=image.rows;
    //координаты новых углов трапеции найдём через QTransform
    //QTransform расчитывается относительно точки (0,0). Не всегда очевидно:
    //для нас центральная точка - это QPoint(imgPoints(0,0),imgPoints(1,0)) m_pointNUmb==0
    QTransform transform=QTransform();
    transform.translate(imgPoints.at<double>(0,0),imgPoints.at<double>(1,0));
    transform.rotate(qRadiansToDegrees(rotation.at<double>(0)),Qt::XAxis);
    transform.rotate(-qRadiansToDegrees(rotation.at<double>(1)),Qt::YAxis);
    transform.rotate(-qRadiansToDegrees(rotation.at<double>(2)),Qt::ZAxis);
    transform.translate(-imgPoints.at<double>(0,0),-imgPoints.at<double>(1,0));
    QRect srcRect=QRect(0,0,width,height);
    QPolygon polygon=transform.mapToPolygon(srcRect);
    //само преобразование через матрицу гомографии
    std::vector<cv::Point2f> src;
    src.push_back(cv::Point2f(0,0));
    src.push_back(cv::Point2f(width,0));
    src.push_back(cv::Point2f(width,height));
    src.push_back(cv::Point2f(0,height));
    std::vector<cv::Point2f> dst;
    dst.push_back(cv::Point2f(polygon.point(0).x(),polygon.point(0).y()));
    dst.push_back(cv::Point2f(polygon.point(1).x(),polygon.point(1).y()));
    dst.push_back(cv::Point2f(polygon.point(2).x(),polygon.point(2).y()));
    dst.push_back(cv::Point2f(polygon.point(3).x(),polygon.point(3).y()));
    cv::Mat homo=cv::findHomography(src,dst,CV_RANSAC,5.);
    cv::Mat image2;
    cv::warpPerspective(image,image2,homo,cv::Size());
    cv::imshow("ooooo",image2);
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
