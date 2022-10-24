#pragma once

#include <QObject>
#include <opencv2/opencv.hpp>

class Calibration : public QObject
{
    Q_OBJECT
public:
    Calibration(int boardWidth, int boardHeight, QObject *parent = nullptr);

signals:
    void newFrame(cv::Mat frame);
public slots:
    void updateFrame(cv::Mat frame);
private:
    cv::Size m_boardSize;
    int m_cornersCount;

};
