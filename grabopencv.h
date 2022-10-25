#pragma once

#include <QObject>
#include <QTimer>
#include <opencv2/opencv.hpp>

class GrabOpenCV : public QObject
{
    Q_OBJECT
public:
    explicit GrabOpenCV(QObject *parent = nullptr, int _width=1920, int _height=1080);
    Q_PROPERTY(bool enable READ getEnable NOTIFY enableChanged)
    bool getEnable() {return m_enable;}
    Q_INVOKABLE void startGrab(int number=0);
    Q_INVOKABLE void stopGrab();
signals:
    void newFrame(const cv::Mat frame);
    void enableChanged();
private:
    cv::VideoCapture* cap;
    QTimer* timer;
    cv::Mat frame;
    bool m_enable=false;
    void timeOut();
    int width;
    int height;
};

