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
    //std::cout<< contour<<std::endl;
    cv::imshow("contours",workImage);

    //lets try found center of circle
    cv::Mat newFrame=cv::Mat(image3.rows,image3.cols,image3.type());
    cv::drawContours(newFrame,contours,number,cv::Scalar(255));
    //find extreme point - left, right, up, down
    std::vector<int> extremeValue{newFrame.cols,0,newFrame.rows,0};
    std::vector<cv::Point> extremePoint{cv::Point(),cv::Point(),cv::Point(),cv::Point()};
    for (size_t i=0; i<contour.size(); i++) {
        cv::Point p=contour.at(i);
        if (p.x<extremeValue.at(0)) {extremePoint.at(0)=p; extremeValue.at(0)=p.x;}
        if (p.x>extremeValue.at(1)) {extremePoint.at(1)=p; extremeValue.at(1)=p.x;}
        if (p.y<extremeValue.at(2)) {extremePoint.at(2)=p; extremeValue.at(2)=p.y;}
        if (p.y>extremeValue.at(3)) {extremePoint.at(3)=p; extremeValue.at(3)=p.y;}
    }
    for (size_t i=0; i<4; i++) cv::circle(newFrame,extremePoint.at(i),5,cv::Scalar(255));
    std::vector<cv::Point2f> extremeCenter{cv::Point2f(),cv::Point2f(),cv::Point2f(),cv::Point2f()};
    std::vector<float> extremeRadius(0,4);
    cv::minEnclosingCircle()



    cv::imshow("newframe",newFrame);
}

void Docking::setThreshold(int val)
{
    threshold=val;
    findCircle();
    emit thresholdChanged(val);
}
