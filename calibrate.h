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
#include "matrixmanager.h"

class Calibrate;

struct Task {
    QString fileName;
    cv::Mat corners;
    cv::vector<cv::Point3f> object;
    float squareSize;
    cv::Size boardSize;
    cv::Size frameSize;
    cv::TermCriteria criteria;
    bool success;
};

class Calibrate : public QObject
{
    Q_OBJECT
public:
    // есть разночтения - учитывать ли squareSize (т.е. размер квадрата доски) ИМЕННО КВАДРАТА! ровного
   // boardWidth и boardHeight кол-во углов доски
    Calibrate(AppConfigMini* appConfig, MatrixManager* matManager, QObject *parent = nullptr);
    ~Calibrate();

    Q_PROPERTY(double workingTime READ getWorkingTime NOTIFY workingTimeChanged)
    double  getWorkingTime() {return m_workingTime/1000.;}

    Q_PROPERTY(int successFrame READ getSuccessFrame NOTIFY successFrameChanged)
    int  getSuccessFrame() {return m_succesFrame;}

    Q_PROPERTY(int inputFrames READ getInputFrames NOTIFY inputFramesChanged)
    int getInputFrames() {return m_inputFrames;}

    Q_PROPERTY(double errorRMS READ getErrorRMS NOTIFY errorRMSChanged)
    double getErrorRMS() {return m_errorRMS;}

    Q_INVOKABLE void start(QString url, QStringList fileName);

signals:
    void workingTimeChanged();
    void successFrameChanged();
    void errorRMSChanged();
    void inputFramesChanged();
public slots:

protected:

private:
    AppConfigMini* m_appConfig;
    cv::Mat* cameraMatrix;
    MatModel* cameraModel;
    cv::Mat* distMatrix;
    MatModel* distModel;
    QString tempDir;
    double m_workingTime=0.;
    int m_inputFrames=0.;
    int m_succesFrame=0;
    double m_errorRMS=0.;
    void removeDir();
    bool reloadDir();
    QStringList toString(cv::Mat mat);
};
