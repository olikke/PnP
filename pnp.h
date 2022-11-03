#pragma once
#include <QObject>
#include <QUrl>
#include <QDebug>
#include <QPointF>
#include <QtMath>
#include <opencv2/opencv.hpp>
#include "matModel.h"
#include "appconfigMini.h"

class PnP : public QObject
{
    Q_OBJECT
public:
    PnP(AppConfigMini* appConfig,QObject *parent = nullptr);

    Q_INVOKABLE void openMatrix(QString url);

    Q_INVOKABLE MatModel* getCameraModel() {return cameraModel;}

    Q_INVOKABLE MatModel* getDistModel() {return distModel;}

    Q_INVOKABLE MatModel* getImgModel() {return imgModel;}

    Q_INVOKABLE MatModel* getObjModel() {return objModel;}

    Q_INVOKABLE void openImage(QString url);

    Q_INVOKABLE void findPoint(QPointF point);

    Q_PROPERTY(int pointNumb READ getPointNumb WRITE setPointNumb NOTIFY pointNumbChanged)
    int getPointNumb() {return m_pointNumb;}
    void setPointNumb(int numb);

    Q_INVOKABLE void changePointNumb(bool incNumb);

    Q_PROPERTY(bool ready READ getReady NOTIFY readyChanged)
    bool getReady() {return m_ready;}

    Q_INVOKABLE void start();
signals:
    void newFrame(const cv::Mat frame);
    void radiusChanged(int);
    void pointNumbChanged(int);
    void paintTarget(int numb, QPointF point);
    void clearTarget(int numb);
    void clearAll();
    void readyChanged();
public slots:
    void squareSizeChanged(int value);
private:
    AppConfigMini* m_appConfig;
    cv::Mat cameraMatrix;
    cv::Mat distMatrix;
    cv::Mat imgPoints;
    cv::Mat objPoints;
    MatModel* cameraModel;
    MatModel* distModel;
    MatModel* imgModel;
    MatModel* objModel;
    cv::Mat image;
    int m_radius=0;
    void findChessboardCorners();
    cv::Mat corners;
    int m_pointNumb=0;
    void clearImgMatrix();
    void calcObjPoint();
    bool m_ready=false;
    void clearCameraMatrix();
};
