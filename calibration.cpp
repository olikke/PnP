#include "calibration.h"

Calibration::Calibration(QObject *parent,int boardWidth, int boardHeight) : QObject(parent)
{
    m_boardSize=cv::Size(boardWidth,boardHeight);
    m_cornersCount=boardWidth*boardHeight;

}

void Calibration::openFile(QString fileName)
{
    cv::Mat frame=cv::imread(fileName.toLatin1().constData());
    updateFrame(frame);
    cv::imwrite(fileName.toLatin1().constData(),frame);
}

//result=cv::calibrateCamera(
//objectPoints для всех одинаков like (0,0,0), (1,0,0), (2,0,0) ....,(6,5,0)
//imagePoints== corners
//result - ско повторного проецирования, пиксель

void Calibration::updateFrame(cv::Mat &frame)
{
    cv::Mat corners;
    //критерии поиска субпикселя кол-во итераций и точность
    const cv::TermCriteria critaria=cv::TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,30,0.1);
    cv::cvtColor(frame,frame,CV_BGR2GRAY);
    bool found=cv::findChessboardCorners(frame,m_boardSize,corners);
    if (found) {
        //olikke cv::Size(11,11) зона поиска - изменение/производительность/точность
        // cv::Size(-1,-1) мёртвая зона
        cv::cornerSubPix(frame,corners,cv::Size(11,11),cv::Size(-1,-1),critaria);
        cv::cvtColor(frame,frame,CV_GRAY2BGR);
        cv::drawChessboardCorners(frame,m_boardSize,corners,found);
    }
}
