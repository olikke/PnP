#pragma once

#include <QObject>
#include <opencv2/opencv.hpp>
#include "matModel.h"
#include "appconfigMini.h"

class MatrixManager : public QObject
{
    Q_OBJECT
public:
    explicit MatrixManager(AppConfigMini* appConfigMini, QObject *parent = nullptr);

    Q_INVOKABLE MatModel* getCameraModel() {return cameraModel;}  // просмотр модели внутренних параметров камеры (калибровки)

    Q_INVOKABLE MatModel* getDistModel() {return distModel;} //просмотр модели коэфф искажений

    Q_INVOKABLE void openMatrix(QString url);  //открыть матрицы калибровки и коэфф искажений

     Q_INVOKABLE void save(QString url);

    Q_PROPERTY(bool ready READ getReady NOTIFY readyChanged)  //готовность к позиционированию
    bool getReady() {return m_ready;}

    cv::Mat*  getCameraMatrix() {return &cameraMatrix;}
    cv::Mat* getDistMatrix() {return &distMatrix;}

signals:
    void readyChanged();
private:
    AppConfigMini* appConfig;
    cv::Mat cameraMatrix;
    cv::Mat distMatrix;
    MatModel* cameraModel;
    MatModel* distModel;
    bool m_ready=false;
    void clearCameraMatrix();
};
