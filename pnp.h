#pragma once
#include <QObject>
#include <QUrl>
#include <QDebug>
#include <QPointF>
#include <QtMath>
#include <QTransform>
#include <QPolygon>
#include <QDateTime>
#include <QMatrix4x4>
#include <opencv2/opencv.hpp>
#include "matModel.h"
#include "appconfigMini.h"
#include "matrixmanager.h"

class PnP : public QObject
{
    Q_OBJECT
public:
    PnP(AppConfigMini* appConfig, MatrixManager* matManager, QObject *parent = nullptr);

    Q_INVOKABLE MatModel* getImage2DModel() {return image2DModel;} //координаты точек проекции объекта кадре

    Q_INVOKABLE MatModel* getImage3DModel() {return image3DModel;} //координаты точек объекта в пространстве

    Q_INVOKABLE void openImage(QString url);

    Q_INVOKABLE void findPoint(QPointF point);

    Q_PROPERTY(int pointNumb READ getPointNumb WRITE setPointNumb NOTIFY pointNumbChanged)
    int getPointNumb() {return m_pointNumb;}
    void setPointNumb(int numb);

    Q_INVOKABLE void changePointNumb(bool incNumb);

    Q_INVOKABLE void start(); //запуск позиционирования

    Q_PROPERTY(bool pnpReady READ getPnpReady NOTIFY pnpReadyChanged) //удачное завершение позициоонирования
    bool getPnpReady() {return m_pnpReady;}

    Q_INVOKABLE MatModel* getRotation() {return rotModel;} // модель итоговой матрицы поворота

    Q_INVOKABLE MatModel* getTranslation() {return transModel;} //модель итоговой матрицы переноса

    Q_INVOKABLE void recoveryOpenCV(); //проецирование по результатам rvec и tvec по методу opencv

    Q_INVOKABLE MatModel* getRecoveryOpenCV() {return recovery2DModel;} //координаты точек проекции объекта пересчитанные по результатам rvec и tvec

    Q_INVOKABLE void recoveryObskur(); //проецирование по результатам rvec и tvec уравнением камеры Обскура

    Q_INVOKABLE MatModel* getRecoveryObskur() {return recovery2DObskurModel;}

    Q_INVOKABLE void reTransform();

signals:
    void newFrame(const cv::Mat frame);
    void pointNumbChanged(int);
    void paintTarget(int numb, QPointF point);
    void clearTarget(int numb);
    void clearAll();
    void readyChanged();
    void pnpReadyChanged();
    void errorChanged();
public slots:
    void squareSizeChanged(int value);
private:
    AppConfigMini* m_appConfig;
    cv::Mat* cameraMatrix;
    cv::Mat* distMatrix;
    cv::Mat points2D;
    cv::Mat points3D;
    cv::Mat rotation;
    cv::Mat translation;
    cv::Mat recovery2D;
    cv::Mat recovery2DObskur;
    MatModel* cameraModel;
    MatModel* distModel;
    MatModel* image2DModel;
    MatModel* image3DModel;
    MatModel* rotModel;
    MatModel* transModel;
    MatModel* recovery2DModel;
    MatModel* recovery2DObskurModel;
    std::vector<cv::Point3d> objVector;
    cv::Mat image;
    int m_radius=0;
    void findChessboardCorners();
    cv::Mat corners;
    int m_pointNumb=0;
    void clearImgMatrix();
    void calcObjPoint();
    bool m_ready=false;
    bool m_pnpReady=false;
    int m_error=1;
};
