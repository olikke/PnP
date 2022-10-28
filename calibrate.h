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
#include "matdisplaymodel.h"

class Calibrate;

struct Task {
    Calibrate* app;
    QString fileName;
    cv::Mat corners;
    cv::vector<cv::Point3f> object;
    float squareSize;
    bool success;
};

class Calibrate : public QObject
{
    Q_OBJECT
public:
    // есть разночтения - учитывать ли squareSize (т.е. размер квадрата доски) ИМЕННО КВАДРАТА! ровного
   // boardWidth и boardHeight кол-во углов доски
    Calibrate(QObject *parent = nullptr, int boardWidth=9, int boardHeight=7, float squareSize=0.02);
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

    Q_PROPERTY(double errorRMS READ getErrorRMS NOTIFY errorRMSChanged)
    double getErrorRMS() {return m_errorRMS;}

    Q_INVOKABLE void start(QString url, QStringList fileName);

    Q_INVOKABLE MatModel* getCameraMatrix() {return cameraModel;};

    cv::Size boardSize() {return m_boardSize;}
signals:
    void iterationsChanged();
    void epsilonChanged();
    void workingTimeChanged();
    void successFrameChanged();
    void errorRMSChanged();
public slots:

protected:

private:
    cv::Mat cameraMatrix;
    MatModel* cameraModel;
    QString tempDir;
    cv::Size m_boardSize;
    float m_squareSize;
    int m_iterations=30;
    double m_epsilon=0.1;
    int m_epsilonDivider=100;
    double m_workingTime=0.;
    int m_succesFrame=0;
    double m_errorRMS=0.;
    void removeDir();
    bool reloadDir();
    cv::vector<cv::Point3f> objPointsConst;
    cv::vector<cv::vector<cv::Point3f>> objPoints; //координаты углов в пространстве
    cv::vector<cv::vector<cv::Point2f>> imgPoints; //координаты углов на изображении (найденные с субпиксельной точностью)
    QStringList toString(cv::Mat mat);
};
