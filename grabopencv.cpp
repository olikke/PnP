#include "grabopencv.h"

GrabOpenCV::GrabOpenCV(MatrixManager* matrixManager, QObject *parent, int _width, int _height):
    QObject(parent),
    cameraMatrix(matrixManager->getCameraMatrix()),
    distMatrix(matrixManager->getDistMatrix()),
    timer(new QTimer(this)),
    m_width(_width),
    m_height(_height)
{
    timer->setInterval(40);
    QObject::connect(timer,&QTimer::timeout,this,&GrabOpenCV::timeOut);
}

void GrabOpenCV::startGrab(int number)
{
    if (number<0)  return;
    stopGrab();
    cap=new cv::VideoCapture(number);
    cap->set(CV_CAP_PROP_FRAME_WIDTH,m_width);
    cap->set(CV_CAP_PROP_FRAME_HEIGHT,m_height);
    m_play=true;
    emit playChanged();
    timer->start(40);
}

void GrabOpenCV::stopGrab()
{
    timer->stop();
    m_play=false;
    emit playChanged();
    if (cap) {
        cap->release();
        cap=nullptr;
    }
}

void GrabOpenCV::setUrl(QString url)
{
    m_path=QUrl(url).toLocalFile();
    emit folderReadyChanged();
}

void GrabOpenCV::makePhoto()
{
    cv::imwrite(QString(m_path+QTime::currentTime().toString("hhmmss.zzz")+".bmp").toLatin1().constData(),frame);
}

void GrabOpenCV::timeOut()
{
    *cap>>frame;
    if (frame.empty())  {
        stopGrab();
        return;
    }
    cv::cvtColor(frame,frame,CV_BGR2GRAY);
    if (m_undistort) {
        cv::Mat und;
        cv::Mat newCameraMatrix1=cv::getOptimalNewCameraMatrix(*cameraMatrix,*distMatrix,frame.size(),1,frame.size());
        cv::undistort(frame,und,*cameraMatrix,*distMatrix,newCameraMatrix1);
        emit newFrame(und);
    } else   emit newFrame(frame);
}
