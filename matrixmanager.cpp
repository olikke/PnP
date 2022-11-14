#include "matrixmanager.h"

MatrixManager::MatrixManager(AppConfigMini* appConfigMini, QObject *parent):
    QObject(parent),
    appConfig(appConfigMini),
    cameraMatrix(cv::Mat(3,3,CV_64FC1)),
    distMatrix(cv::Mat(1,5,CV_64FC1)),
    cameraModel(new MatModel(&cameraMatrix,this)),
    distModel(new MatModel(&distMatrix,this))
{
    appConfig->getMatrixFileName().isEmpty()?
                clearCameraMatrix():
                openMatrix(appConfig->getMatrixFileName());
}

void MatrixManager::openMatrix(QString url)
{
    cv::FileStorage fs(QUrl(url).toLocalFile().toLatin1().constData(), cv::FileStorage::READ);
    if(!fs.isOpened()){
        qDebug()<<"Не удаётся открыть файл";
        clearCameraMatrix();
        m_ready=false;
        emit readyChanged();
        return;
    }
    appConfig->setMatrixFileName(url);
    fs["DistorsionMatrix"]>>distMatrix;
    fs["CameraMatrix"]>>cameraMatrix;
    cameraModel->update();
    distModel->update();
    m_ready=true;
    emit readyChanged();
}

void MatrixManager::save(QString url)
{
    cv::FileStorage fs(QUrl(url).toLocalFile().toLatin1().constData(), cv::FileStorage::WRITE);
    fs<<"CameraMatrix"<<cameraMatrix;
    fs<<"DistorsionMatrix"<<distMatrix;
    appConfig->setMatrixFileName(url);
}

void MatrixManager::clearCameraMatrix()
{
    cameraMatrix=cv::Mat::zeros(cameraMatrix.rows,cameraMatrix.cols,cameraMatrix.type());
    cameraModel->update();
    distMatrix=cv::Mat::zeros(distMatrix.rows,distMatrix.cols,distMatrix.type());
    distModel->update();
}
