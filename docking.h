#pragma once

#include <QObject>
#include <QtMath>
#include "matModel.h"
#include "appconfigMini.h"
#include "matrixmanager.h"


class Docking : public QObject
{
    Q_OBJECT
public:
    Docking(AppConfigMini* appConfig, MatrixManager* matManager,QObject *parent = nullptr);

    Q_INVOKABLE void openImage(QString url);

    Q_INVOKABLE void findCircle();

    Q_PROPERTY(int threshold READ getThreshold WRITE setThreshold NOTIFY thresholdChanged)
    int getThreshold() {return threshold;}
    void setThreshold(int val);
signals:
    void newFrame(const cv::Mat frame);
    void thresholdChanged(int);
public slots:

private:
    AppConfigMini* m_appConfig;
    cv::Mat* cameraMatrix;
    cv::Mat* distMatrix;
    cv::Mat image;
    int threshold=150;
};
