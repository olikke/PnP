#pragma once

#include <QObject>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include <QUrl>
#include <QFile>
#include <QtConcurrent/QtConcurrent>
#include <opencv2/opencv.hpp>
#include "global.h"
#include "matModel.h"
#include "appconfigMini.h"

class Calibrate;

struct Task {
    QString fileName;
    cv::Mat corners;
    cv::vector<cv::Point3f> object;
    float squareSize;
    cv::Size boardSize;
    cv::Size frameSize;
    bool success;
};

class Calibrate : public QObject
{
    Q_OBJECT
public:
    // есть разночтения - учитывать ли squareSize (т.е. размер квадрата доски) ИМЕННО КВАДРАТА! ровного
   // boardWidth и boardHeight кол-во углов доски
    Calibrate(QObject *parent = nullptr,AppConfigMini* appConfig=nullptr);
    ~Calibrate();

    //кол-во итераций поиска субпикселей углов
    Q_PROPERTY(int iterations READ getIterations WRITE setIterations NOTIFY iterationsChanged)
    int getIterations() {return m_iterations;}
    void setIterations(int val) {m_iterations=val;}

    //точность поиска субпикселей углов
    Q_PROPERTY(int epsilon READ getEpsilon WRITE setEpsilon NOTIFY epsilonChanged)
    int getEpsilon() {return qCeil(m_epsilon*m_epsilonDivider);}
    void setEpsilon(int val) {m_epsilon=val/m_epsilonDivider;}

    Q_PROPERTY(int epsilonDivider READ getEpsilonDivider CONSTANT)
    int getEpsilonDivider() {return m_epsilonDivider;}

    Q_PROPERTY(double workingTime READ getWorkingTime NOTIFY workingTimeChanged)
    double  getWorkingTime() {return m_workingTime/1000.;}

    Q_PROPERTY(int successFrame READ getSuccessFrame NOTIFY successFrameChanged)
    int  getSuccessFrame() {return m_succesFrame;}

    Q_PROPERTY(int inputFrames READ getInputFrames NOTIFY inputFramesChanged)
    int getInputFrames() {return m_inputFrames;}

    Q_PROPERTY(double errorRMS READ getErrorRMS NOTIFY errorRMSChanged)
    double getErrorRMS() {return m_errorRMS;}

    Q_INVOKABLE void start(QString url, QStringList fileName);

    Q_INVOKABLE MatModel* getCameraModel() {return cameraModel;}

    Q_INVOKABLE MatModel* getDistModel() {return distModel;}

    Q_INVOKABLE void save(QString url);

signals:
    void iterationsChanged();
    void epsilonChanged();
    void workingTimeChanged();
    void successFrameChanged();
    void errorRMSChanged();
    void inputFramesChanged();
public slots:

protected:

private:
    AppConfigMini* m_appConfig;
    cv::Mat cameraMatrix;
    MatModel* cameraModel;
    cv::Mat distMatrix;
    MatModel* distModel;
    QString tempDir;
    int m_iterations=30;
    double m_epsilon=0.1;
    int m_epsilonDivider=100;
    double m_workingTime=0.;
    int m_inputFrames=0.;
    int m_succesFrame=0;
    double m_errorRMS=0.;
    void removeDir();
    bool reloadDir();
    QStringList toString(cv::Mat mat);
};
