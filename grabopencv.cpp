#include "grabopencv.h"

GrabOpenCV::GrabOpenCV(QObject *parent, int _width, int _height):
    QObject(parent),
    timer(new QTimer(this)),
    width(_width),
    height(_height)
{
    timer->setInterval(40);
    QObject::connect(timer,&QTimer::timeout,this,&GrabOpenCV::timeOut);
}

void GrabOpenCV::startGrab(int number)
{
    if (number<0)  return;
    stopGrab();
    cap=new cv::VideoCapture(number);
    cap->set(CV_CAP_PROP_FRAME_WIDTH,width);
    cap->set(CV_CAP_PROP_FRAME_HEIGHT,height);
    timer->start(40);
}

void GrabOpenCV::stopGrab()
{
    timer->stop();
    m_enable=false;
    emit enableChanged();
    if (cap) {
        cap->release();
        cap=nullptr;
    }
}

void GrabOpenCV::timeOut()
{
    *cap>>frame;
    if (frame.empty()) {
        if (m_enable) {
            m_enable=false;
            emit enableChanged();
        }
        return;
    }
    cv::cvtColor(frame,frame,CV_BGR2GRAY);
    emit newFrame(frame);
    if (!m_enable) {
        m_enable=true;
        emit enableChanged();
    }
}
