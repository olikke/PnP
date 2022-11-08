#pragma once
#include <QObject>
#include <QUrl>
#include <QDebug>
#include <QPointF>
#include <QtMath>
#include <QTransform>
#include <QPolygon>
#include <QDateTime>
#include <opencv2/opencv.hpp>
#include "matModel.h"
#include "appconfigMini.h"

class PnP : public QObject
{
    Q_OBJECT
public:
    PnP(AppConfigMini* appConfig,QObject *parent = nullptr);

    Q_INVOKABLE void openMatrix(QString url);  //открыть матрицы калибровки и коэфф искажений

    Q_INVOKABLE MatModel* getCameraModel() {return cameraModel;}  // просмотр модели внутренних параметров камеры (калибровки)

    Q_INVOKABLE MatModel* getDistModel() {return distModel;} //просмотр модели коэфф искажений

    Q_INVOKABLE MatModel* getImgModel() {return imgModel;} //координаты точек проекции объекта кадре

    Q_INVOKABLE MatModel* getObjModel() {return objModel;} //координаты точек объекта в пространстве

    Q_INVOKABLE void openImage(QString url);

    Q_INVOKABLE void findPoint(QPointF point);

    Q_PROPERTY(int pointNumb READ getPointNumb WRITE setPointNumb NOTIFY pointNumbChanged)
    int getPointNumb() {return m_pointNumb;}
    void setPointNumb(int numb);

    Q_INVOKABLE void changePointNumb(bool incNumb);

    Q_PROPERTY(bool ready READ getReady NOTIFY readyChanged)  //готовность к позиционированию
    bool getReady() {return m_ready;}

    Q_INVOKABLE void start(); //запуск позиционирования

    Q_PROPERTY(bool pnpReady READ getPnpReady NOTIFY pnpReadyChanged) //удачное завершение позициоонирования
    bool getPnpReady() {return m_pnpReady;}

    Q_INVOKABLE MatModel* getRotation() {return rotModel;} // модель итоговой матрицы поворота

    Q_INVOKABLE MatModel* getTranslation() {return transModel;} //модель итоговой матрицы переноса

    Q_PROPERTY(int error READ getError WRITE setError NOTIFY errorChanged) //ошибка вычисления пикселя
    bool getError() {return m_error;}
    void setError(int val) {m_error=val;}

    Q_INVOKABLE MatModel* getRotationErr() {return rotModelErr;} // модель итоговой матрицы поворота

    Q_INVOKABLE MatModel* getTranslationErr() {return transModelErr;} //модель итоговой матрицы переноса

    Q_INVOKABLE void antiRotate();  //восстановление изображения по матрице поворота (для оценки результата)
signals:
    void newFrame(const cv::Mat frame);
    void radiusChanged(int);
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
    cv::Mat cameraMatrix;
    cv::Mat distMatrix;
    cv::Mat imgPoints;
    cv::Mat objPoints;
    cv::Mat rotation;
    cv::Mat translation;
    cv::Mat rotationErr;
    cv::Mat translationErr;
    MatModel* cameraModel;
    MatModel* distModel;
    MatModel* imgModel;
    MatModel* objModel;
    MatModel* rotModel;
    MatModel* transModel;
    MatModel* rotModelErr;
    MatModel* transModelErr;
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
    void clearCameraMatrix();
};
