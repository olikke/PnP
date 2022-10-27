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

class Calibrate;

struct Task {
    Calibrate* app;
    QString fileName;
    cv::Mat corners;
    bool success;
};

class Calibrate : public QObject
{
    Q_OBJECT
public:
    // есть разночтения - учитывать ли squareSize (т.е. размер квадрата доски) ИМЕННО КВАДРАТА! ровного
   // boardWidth и boardHeight кол-во углов доски
    Calibrate(QObject *parent = nullptr, int boardWidth=8, int boardHeight=5, float squareSize=29.);
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

    Q_PROPERTY(double timeFindCorners READ getTimeFindCorners NOTIFY timeFindCornersChanged)
    double  getTimeFindCorners() {return m_timeFindCorners/1000.;}

    Q_INVOKABLE void start(QString url, QStringList fileName);

    cv::Size boardSize() {return m_boardSize;}
signals:
    void iterationsChanged();
    void epsilonChanged();
    void timeFindCornersChanged();
public slots:

protected:

private:
    QString tempDir;
    cv::Size m_boardSize;
    int m_iterations=30;
    double m_epsilon=0.1;
    int m_epsilonDivider=100;
    double m_timeFindCorners=0.;
    void removeDir();
    bool reloadDir();
    cv::vector<cv::Point3f> objPointsConst;
    cv::vector<cv::vector<cv::Point3f>> objPoints; //координаты углов в пространстве
    cv::vector<cv::vector<cv::Point2f>> imgPoints; //координаты углов на изображении (найденные с субпиксельной точностью)
    QStringList toString(cv::Mat mat);
};
