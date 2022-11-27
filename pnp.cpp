#include "pnp.h"
//https://stackoverflow-com.translate.goog/questions/45458665/get-correct-rvec-and-tvec-for-camera-pose-estimation-from-solvpnp-function-in-op?_x_tr_sl=en&_x_tr_tl=ru&_x_tr_hl=ru&_x_tr_pto=sc
//https://docs.opencv.org/4.x/d9/dab/tutorial_homography.html
//https://gist-github-com.translate.goog/dbcesar/421c4c291b229615cc6a?_x_tr_sl=en&_x_tr_tl=ru&_x_tr_hl=ru&_x_tr_pto=sc
//https://gist.github.com/dbcesar/421c4c291b229615cc6a
//https://www.guivi.one/2019/11/19/projecting-point-to-world-coordinate/
//https://stackoverflow-com.translate.goog/questions/12299870/computing-x-y-coordinate-3d-from-image-point?_x_tr_sl=en&_x_tr_tl=ru&_x_tr_hl=ru&_x_tr_pto=sc
//https://stackoverflow.com/questions/12299870/computing-x-y-coordinate-3d-from-image-point

//MAIN
//http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToAngle/index.htm
//https://ru.stackoverflow.com/questions/756331/%D0%9F%D0%BE%D0%B2%D0%BE%D1%80%D0%BE%D1%82-%D0%BE%D0%B1%D1%8A%D0%B5%D0%BA%D1%82%D0%B0-%D0%B2-%D0%BF%D1%80%D0%BE%D1%81%D1%82%D1%80%D0%B0%D0%BD%D1%81%D1%82%D0%B2%D0%B5

PnP::PnP(AppConfigMini* appConfig, MatrixManager* matManager,QObject *parent) :
    QObject(parent),
    m_appConfig(appConfig),
    cameraMatrix(matManager->getCameraMatrix()),
    distMatrix(matManager->getDistMatrix()),
    points2D(cv::Mat(2,5,CV_64FC1)),
    points3D(cv::Mat(3,5,CV_64FC1)),
    rotation(cv::Mat(1,3,CV_64FC1)),
    translation(cv::Mat(1,3,CV_64FC1)),
    recovery2D(cv::Mat(2,5,CV_64FC1)),
    recovery2DObskur(cv::Mat(2,5,CV_64FC1)),
    cameraModel(matManager->getCameraModel()),
    distModel(matManager->getDistModel()),
    image2DModel(new MatModel(&points2D,this)),
    image3DModel(new MatModel(&points3D,this)),
    rotModel(new MatModel(&rotation,this)),
    transModel(new MatModel(&translation,this)),
    recovery2DModel(new MatModel(&recovery2D,this)),
    recovery2DObskurModel(new MatModel(&recovery2DObskur,this))
{
    qsrand(static_cast<unsigned int>(QDateTime::currentMSecsSinceEpoch()));
    points2D=cv::Mat::zeros(points2D.rows,points2D.cols,points2D.type());
    recovery2D=cv::Mat::zeros(recovery2D.rows,recovery2D.cols,recovery2D.type());
    recovery2DObskur=cv::Mat::zeros(recovery2DObskur.rows,recovery2DObskur.cols,recovery2DObskur.type());
    image2DModel->update();
    recovery2DModel->update();
    recovery2DObskurModel->update();
    clearImgMatrix();
    m_radius=appConfig->getSquareSize();
    calcObjPoint();
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
    points2D.at<double>(0,m_pointNumb)=static_cast<double>(corners.at<cv::Vec2f>(numb)[0]);
    points2D.at<double>(1,m_pointNumb)=static_cast<double>(corners.at<cv::Vec2f>(numb)[1]);
    emit paintTarget(m_pointNumb,QPointF(points2D.at<double>(0,m_pointNumb),
                                         points2D.at<double>(1,m_pointNumb)));
    image2DModel->update();
}

void PnP::setPointNumb(int numb)
{
   if (numb<0 || numb>distMatrix->cols-1) return;
   m_pointNumb=numb;
   emit pointNumbChanged(numb);
   image2DModel->highlightColumn(m_pointNumb);
}

void PnP::changePointNumb(bool incNumb)
{
    int v= incNumb?
               m_pointNumb==distMatrix->cols-1? 0: m_pointNumb+1:
               m_pointNumb==0? distMatrix->cols-1 : m_pointNumb-1;
    setPointNumb(v);
}

void PnP::start()
{
    objVector.clear();
    for (int i=0; i<points3D.cols; i++) {
        objVector.push_back(cv::Point3d(points3D.at<double>(0,i),points3D.at<double>(1,i),points3D.at<double>(2,i)));
    }
    std::vector<cv::Point2f>imgVector;
    for (int i=0; i<points2D.cols; i++)
        imgVector.push_back(cv::Point2d(points2D.at<double>(0,i),points2D.at<double>(1,i)));
    if (!cv::solvePnP(objVector,imgVector,*cameraMatrix,*distMatrix,rotation,translation)) {
        m_pnpReady=false;
        emit pnpReadyChanged();
        return;
    }
    rotModel->update();
    transModel->update();
    m_pnpReady=true;
    emit pnpReadyChanged();
    reTransform();
}

void PnP::recoveryObskur()
{
    std::vector<cv::Mat> newObjPoints3d;
    for (int i=0; i<points3D.cols; i++)
        newObjPoints3d.push_back((cv::Mat_<double>(3,1)
                                  <<points3D.at<double>(0,i),
                                  points3D.at<double>(1,i),
                                  1));

    cv::Mat rotationMatrix;
    cv::Rodrigues(rotation,rotationMatrix);
    std::cout<<rotationMatrix<<std::endl;

    std::vector<cv::Point2d> temp;
    for (int i=0; i<newObjPoints3d.size(); i++) {
        cv::Mat p=*cameraMatrix*(rotationMatrix*newObjPoints3d.at(i)+translation);
        p/=p.at<double>(2);
        temp.push_back(cv::Point2d(p.at<double>(0),p.at<double>(1)));
        recovery2DObskur.at<double>(0,i)=p.at<double>(0);
        recovery2DObskur.at<double>(1,i)=p.at<double>(1);
    }
    cv::Scalar color=cv::Scalar(0x9b,0x03,0xe5);

    cv::circle(image,temp.at(0),5,color,2);
    cv::line(image,temp.at(1),temp.at(2),color,2);
    cv::line(image,temp.at(2),temp.at(3),color,2);
    cv::line(image,temp.at(3),temp.at(4),color,2);
    cv::line(image,temp.at(4),temp.at(1),color,2);
    emit newFrame(image);
    recovery2DObskurModel->update();   
}

void PnP::reTransform()
{
    /*разборки с rvec
     rvec это единичный вектор * угол Teta
     Едининчный вектор - это ось, вокруг которой мы поворачиваем на угол Тета
     Тогда угол Teta = КОРЕНЬ(rvec[0]*rvec[0]+rvec[1]*rvec[1]+rvec[2]*rvec[2])
     rvec1 = rvec/Teta = (x,y,z)
     Тогда матрица вращения (которую можно расчитать Родригесом) CT - Cos(Teta); ST - Sin(Teta)
     CT+(1-CT)x²        (1-CT)xy-STz       (1-CT)xz+STy
     (1-CT)yx+STz      CT+(1-CT)y²      (1-CT)yz-STx
     (1-CT)zx-STy       (1-CT)zy+STx    CT+(1-CT)z²*/
     double teta=qSqrt(qPow(rotation.at<double>(0),2)+qPow(rotation.at<double>(1),2)+qPow(rotation.at<double>(2),2));
     std::cout<<"normRotation"<<rotation/teta<<std::endl;
     std::cout<<"Teta"<<teta<<std::endl;
     double alfa=qRadiansToDegrees(qAcos(rotation.at<double>(0)/teta));
     double betta=qRadiansToDegrees(qAcos(rotation.at<double>(1)/teta));
     double gamma=qRadiansToDegrees(qAcos(rotation.at<double>(2)/teta));
     std::cout<<"alfa:"<<alfa<<" betta: "<<betta<<" gamma: "<<gamma<<std::endl;

     //rotation matrix to single vector and angle
     //teta = acos(( m00 + m11 + m22 - 1)/2)
     //единичный вектор
     //rvec[0] = (m21 - m12)/√((m21 - m12)2+(m02 - m20)2+(m10 - m01)2)
     //rvec[1] = (m02 - m20)/√((m21 - m12)2+(m02 - m20)2+(m10 - m01)2)
     //rvec[2] = (m10 - m01)/√((m21 - m12)2+(m02 - m20)2+(m10 - m01)2)

     //возьмем точку с координатами rvec[0],rvec[1],rvec[2], затем повернёмся на углы alfa, betta & gamma.
     //тогда координаты этой точки д.б. rvec[0],0,0??

     cv::Mat rotationMatrix;
     cv::Rodrigues(rotation,rotationMatrix);
     cv::Mat m1,m2,m3,m4,m5;

     //https://github.com/opencv/opencv/blob/master/samples/cpp/tutorial_code/calib3d/real_time_pose_estimation/src/Utils.cpp
     //opencv euler rotation y-z-x x-width; y-height; z-distance
     cv::Vec3d v=cv::RQDecomp3x3(rotationMatrix,m1,m2,m3,m4,m5);
     std::cout<<"v"<<v<<std::endl;
     std::cout<<"m1"<<m1<<std::endl;
     std::cout<<"m2"<<m2<<std::endl;
     std::cout<<"m3"<<m3<<std::endl;
     std::cout<<"m4"<<m4<<std::endl;
     std::cout<<"m5"<<m5<<std::endl;


     QRect srcRect=QRect(-m_radius,-m_radius,m_radius*2,m_radius*2);
     QTransform transform=QTransform();
     transform.rotate(v[0],Qt::YAxis);
     transform.rotate(-v[1],Qt::ZAxis);
     transform.rotate(-v[2],Qt::XAxis);
     transform.rotateRadians(teta,Qt::XAxis);
     QPolygon polygon=transform.mapToPolygon(srcRect);
     qDebug()<<polygon;
     //далее формулу обскура но без ротации
     cv::Mat mmm=cv::Mat(3,1,CV_64FC1);
     mmm.at<double>(0,0)=polygon.point(0).x()/*+translation.at<double>(0)*/;
     mmm.at<double>(1,0)=polygon.point(0).y()/*+translation.at<double>(1);*/;
     mmm.at<double>(2,0)=0/*translation.at<double>(2);*/;
     cv::Mat m=cameraMatrix->inv()*(mmm+translation);
     std::cout<<"po"<<m<<std::endl;


//     std::vector<cv::Point2f> src;
//     src.push_back(cv::Point2f(-m_radius,-m_radius));
//     src.push_back(cv::Point2f(m_radius,-m_radius));
//     src.push_back(cv::Point2f(m_radius,m_radius));
//     src.push_back(cv::Point2f(-m_radius,m_radius));
//     std::vector<cv::Point2f> dst;
//     dst.push_back(cv::Point2f(polygon.point(0).x(),polygon.point(0).y()));
//     dst.push_back(cv::Point2f(polygon.point(1).x(),polygon.point(1).y()));
//     dst.push_back(cv::Point2f(polygon.point(2).x(),polygon.point(2).y()));
//     dst.push_back(cv::Point2f(polygon.point(3).x(),polygon.point(3).y()));
//     cv::Mat homo=cv::findHomography(src,dst,CV_RANSAC,5.);
//     cv::warpPerspective(image,image,homo,cv::Size());


}

void PnP::recoveryOpenCV()
{
    std::vector<cv::Point2d> projPoints;
    cv::projectPoints(objVector,rotation,translation,*cameraMatrix,*distMatrix,projPoints);

    for (size_t i=0; i<projPoints.size(); i++) {
        recovery2D.at<double>(0,i)=projPoints.at(i).x;
        recovery2D.at<double>(1,i)=projPoints.at(i).y;
    }
    recovery2DModel->update();
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
    points2D=cv::Mat::zeros(points2D.rows,points2D.cols,points2D.type());
    image2DModel->update();
    image2DModel->highlightColumn(m_pointNumb);
    emit clearAll();
}

void PnP::calcObjPoint()
{
    //z - always 0
    points3D=cv::Mat::zeros(points3D.rows,points3D.cols,points3D.type());
    //central point
    points3D.at<double>(0,0)=0.;
    points3D.at<double>(1,0)=0.;
    //left point
    points3D.at<double>(0,1)=-m_radius*1.;
    points3D.at<double>(1,1)=0.;
    //up point
    points3D.at<double>(0,2)=0;
    points3D.at<double>(1,2)=-m_radius*1.;
    //right point
    points3D.at<double>(0,3)=m_radius*1.;
    points3D.at<double>(1,3)=0.;
    //down point
    points3D.at<double>(0,4)=0;
    points3D.at<double>(1,4)=m_radius*1.;
    image3DModel->update();
}
