#include "pnp.h"

PnP::PnP(QObject *parent) :
    QObject(parent),
    cameraMatrix(cv::Mat(3,3,CV_32FC1)),
    distMatrix(cv::Mat(1,5,CV_32FC1)),
    cameraModel(new MatModel(&cameraMatrix,this)),
    distModel(new MatModel(&distMatrix,this))
{

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
}
