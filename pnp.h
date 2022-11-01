#pragma once
#include <QObject>
#include <QUrl>
#include <QDebug>
#include <opencv2/opencv.hpp>
#include "matModel.h"

class PnP : public QObject
{
    Q_OBJECT
public:
    explicit PnP(QObject *parent = nullptr);

    Q_INVOKABLE void openMatrix(QString url);

    Q_INVOKABLE MatModel* getCameraModel() {return cameraModel;}

    Q_INVOKABLE MatModel* getDistModel() {return distModel;}

    Q_INVOKABLE void openImage(QString url);

signals:
    void newFrame(const cv::Mat frame);
public slots:

private:
        cv::Mat cameraMatrix;
        cv::Mat distMatrix;
        MatModel* cameraModel;
        MatModel* distModel;
        cv::Mat image;
};
