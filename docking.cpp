#include "docking.h"

Docking::Docking(AppConfigMini *appConfig, MatrixManager *matManager, QObject *parent):
    QObject (parent),
    m_appConfig(appConfig),
    cameraMatrix(matManager->getCameraMatrix()),
    distMatrix(matManager->getDistMatrix())
{

}

void Docking::openImage(QString url)
{
    image=cv::imread(QUrl(url).toLocalFile().toLatin1().constData());
    emit newFrame(image);
}

void Docking::findCircle()
{
    if (image.empty()) return;
    cv::Mat image3;
    int scale=2;
    image3.create(static_cast<int>(image.rows/scale),static_cast<int>(image.cols/scale),image.type());
    cv::resize(image,image3,image3.size(),0,0,cv::INTER_LINEAR);
    cvtColor(image3, image3,CV_BGR2GRAY);
    cv::threshold(image3,image3,threshold,255,cv::THRESH_BINARY/*+cv::THRESH_OTSU*/);
    cv::imshow("threshold Before",image3);
//    cv::erode(image3,image3,500);
//    cv::dilate(image3,image3,500);
    cv::imshow("threshold",image3);

    cv::Mat image2=image3.clone();
    cv::SimpleBlobDetector::Params params;
    params.filterByArea=true;
    params.minArea=400;
    params.maxArea=image.cols*image.rows;
    params.filterByColor=true;
    params.blobColor=255;
    params.filterByCircularity=true;
    params.minCircularity=0.75;
    params.maxCircularity=1;
    params.filterByConvexity = true;
    params.minConvexity=0.2;
    params.filterByInertia =false;
    params.minInertiaRatio=0.1;
    params.maxInertiaRatio=1;
    cv::SimpleBlobDetector detector=cv::SimpleBlobDetector(params);
    std::vector<cv::KeyPoint> points;
    detector.detect(image2,points);
    if (points.size()!=0)
    cv::drawKeypoints(image2,points,image2,cv::Scalar(255),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    cv::imshow("blob",image2);
   cv::Mat workImage=image3.clone();

  //  cv::Canny (workImage, workImage, 100, 200 );
    std::vector< cv::vector<cv::Point> > contours;
    cv::findContours(workImage, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    cv::drawContours(workImage,contours,-1,cv::Scalar(255));

    if (contours.size()==0) return;
    double maxLen=0; double len;
    size_t number=contours.size();
    //как то учесть ситуацию, когда контуры приблизительно равны
    for (size_t i=0; i<contours.size();i++)
    {
        if (contours.at(i).size()>=5) {
            len=cv::arcLength(contours[i],true);
            if (len>=maxLen) {
                maxLen=len;
                number=i;
            }
        }
    }
    if (number==contours.size()) return;
    cv::vector<cv::Point> contour = contours.at(number);
    cv::RotatedRect rectangle;
    rectangle=cv::fitEllipse( contour);
    cv::Point2f vertices[4];
    rectangle.points(vertices);
    for (int i=0; i<4; i++) {
        cv::line(workImage,vertices[i],vertices[(i+1)%4],cv::Scalar(255),2);
    }
    std::cout<< contour<<std::endl;
    //давай попробуем разделить длину окружности на 4 и так поставить точки
    std::vector<cv::Point> pointsInContour;
    pointsInContour.push_back(contour.front());
     double ss=qSqrt(qPow(contour.front().x-contour.back().x,2)+qPow(contour.front().y-contour.back().y ,2));
     int k=1;
     double found=maxLen*k/4;
    for (size_t i=1; i<contour.size(); i++) {
       ss+=qSqrt(qPow(contour.at(i-1).x-contour.at(i).x,2)+qPow(contour.at(i-1).y-contour.at(i).y ,2));
       if (ss>found) {
           pointsInContour.push_back(contour.at(i-1));
           k++;
           found=maxLen*k/4;
       }
    }
    std::cout<<"realL="<<maxLen<<" calcL="<<ss<<std::endl;
    for (size_t i=0; i<pointsInContour.size(); i++) {
        cv::circle(workImage,pointsInContour.at(i),5,cv::Scalar(255),2);
    }
    cv::line(workImage,pointsInContour.at(0),pointsInContour.at(2),cv::Scalar(255),2);
    cv::line(workImage,pointsInContour.at(1),pointsInContour.at(3),cv::Scalar(255),2);




    cv::imshow("contours",workImage);
}

void Docking::setThreshold(int val)
{
    threshold=val;
    findCircle();
    emit thresholdChanged(val);
}
