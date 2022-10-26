#pragma once

#include <QObject>
#include <QDir>
#include <opencv2/opencv.hpp>

class Calibration : public QObject
{
    Q_OBJECT
public:
    Calibration(QObject *parent = nullptr, int boardWidth=8, int boardHeight=5);
    void openFile(QString fileName);
public slots:
    void updateFrame(cv::Mat &frame);
private:
    cv::Size m_boardSize;
    int m_cornersCount;

};
