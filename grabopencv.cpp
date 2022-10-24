#include "grabopencv.h"

GrabOpenCV::GrabOpenCV(QObject *parent): QObject(parent), timer(new QTimer(this))
{
    timer->setInterval(40);
    QObject::connect(timer,&QTimer::timeout,this,&GrabOpenCV::timeOut);
}

void GrabOpenCV::startGrab(int number, int width, int height)
{
    if (number<0)  return;
    stopGrab();
    cap=new cv::VideoCapture(number);
    cap->set(CV_CAP_PROP_FRAME_WIDTH,width);
    cap->set(CV_CAP_PROP_FRAME_HEIGHT,height);
    timer->start();
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
    emit newFrame(frame);
    if (!m_enable) {
        m_enable=true;
        emit enableChanged();
    }
}
