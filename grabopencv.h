#pragma once

#include <QObject>
#include <QTimer>
#include <QUrl>
#include <QDebug>
#include <QDateTime>
#include <opencv2/opencv.hpp>

class GrabOpenCV : public QObject
{
    Q_OBJECT
public:
    GrabOpenCV(QObject *parent = nullptr, int _width=1920, int _height=1080);
    Q_PROPERTY(bool play READ getPlay NOTIFY playChanged)
    bool getPlay() {return m_play;}

    Q_PROPERTY(bool folderReady READ getFolderReady NOTIFY folderReadyChanged)
    bool getFolderReady() {return !m_path.isEmpty();}

    Q_INVOKABLE void startGrab(int number=0);
    Q_INVOKABLE void stopGrab();
    Q_INVOKABLE void setUrl(QString url);

    Q_INVOKABLE void makePhoto();
signals:
    void newFrame(const cv::Mat frame);
    void pathChanged();
    void playChanged();
    void folderReadyChanged();
private:
    cv::VideoCapture* cap;
    QTimer* timer;
    cv::Mat frame;
    bool m_play=false;
    void timeOut();
    int m_width;
    int m_height;
    QString m_path="";
};

