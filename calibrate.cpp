#include "calibrate.h"

Calibrate::Calibrate(QObject *parent,AppConfigMini* appConfig) :
    QObject(parent),
    m_appConfig(appConfig),
    cameraMatrix(cv::Mat(3,3,CV_32FC1)),
    cameraModel(new MatModel(/*&cameraMatrix,*/this)),
    tempDir(QCoreApplication::applicationDirPath()+"/.temporary/")
{
    cameraModel->newMat(&cameraMatrix);
  //  m_boardSize=cv::Size(boardWidth,boardHeight);
    if (!reloadDir()) qDebug()<<"Не удалось создать папку для временных файлов";
   //  const cv::Point3f kCenterOffset((float)(m_boardSize.width - 1) * squareSize, (float)(m_boardSize.height - 1) * squareSize, 0.f);
}

Calibrate::~Calibrate()
{
    removeDir();
}

Task calc(const Task &task)
{
    Task newTask=task;
    cv::Mat frame=cv::imread(newTask.fileName.toLatin1().constData());
    cv::Size s=frame.size();
    const cv::TermCriteria criteria=cv::TermCriteria(cv::TermCriteria::EPS+ cv::TermCriteria::COUNT,30, 0.1/*task.app->getIterations(),task.app->getEpsilon()*/);
    cv::cvtColor(frame,frame,CV_BGR2GRAY);
    newTask.success=cv::findChessboardCorners(frame,task.app->boardSize(),newTask.corners);
    if (newTask.success) {
        //olikke cv::Size(11,11) зона поиска - изменение/производительность/точность
        // cv::Size(-1,-1) мёртвая зона
        cv::cornerSubPix(frame,newTask.corners,cv::Size(11,11),cv::Size(-1,-1),criteria);
        cv::cvtColor(frame,frame,CV_GRAY2BGR);
        cv::drawChessboardCorners(frame,task.app->boardSize(),newTask.corners,newTask.success);
        for (int i=0; i<task.app->boardSize().height; i++)
            for (int j=0; j<task.app->boardSize().width;j++)
                newTask.object.push_back(cv::Point3f(j*task.squareSize,i*task.squareSize,0));
    }
    cv::imwrite(newTask.fileName.toLatin1().constData(),frame);
    return newTask;
}

void Calibrate::start(QString url, QStringList fileName)
{
    if (!reloadDir()) {
        m_workingTime=0;
        emit workingTimeChanged();
    }
    std::chrono::high_resolution_clock::time_point time;
    getTime(time);
    QDir source(QUrl(url).toLocalFile());
    QStringList list = source.entryList(QDir::Files | QDir::AllEntries | QDir::NoDotAndDotDot);
    QList<Task> blank;
    for (QString fn: list) {
        if (!fileName.contains(fn)) continue;
        QFile::copy(QUrl(url).toLocalFile()+"/"+fn, tempDir+fn);
        Task task;
        task.app=this;
        task.fileName=tempDir+fn;
        task.squareSize=m_squareSize;
        blank.push_back(task);        
    }
    QList<Task> result=QtConcurrent::blockingMapped(blank,calc);
    m_succesFrame=0;
    //посчитай и выведи кол-во верных кадров
    for (Task task:result) {
        if (!task.success) continue;
        m_succesFrame++;
        objPoints.push_back(task.object);
        imgPoints.push_back(task.corners);
    }
    emit successFrameChanged();
    cv::Mat distCoeffs;
    //https://stackoverflow-com.translate.goog/questions/53277597/fundamental-understanding-of-tvecs-rvecs-in-opencv-aruco?_x_tr_sl=en&_x_tr_tl=ru&_x_tr_hl=ru&_x_tr_pto=sc
    cv::_OutputArray rotation;
    cv::_OutputArray translation;
    int flags = 0;//cv::CALIB_USE_INTRINSIC_GUESS | cv::CALIB_FIX_PRINCIPAL_POINT | cv::CALIB_RATIONAL_MODEL;
    m_errorRMS=cv::calibrateCamera(objPoints,imgPoints,cv::Size(1920,1200),cameraMatrix,distCoeffs,rotation,translation,flags,cv::TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,m_iterations,m_epsilon));

    emit errorRMSChanged();
    qDebug()<<"";
    qDebug()<<toString(cameraMatrix);
    qDebug()<<"";
        cameraModel->updateMat(/*cameraMatrix*/);
//    qDebug()<<"";
//    qDebug()<<toString(distCoeffs);
    m_workingTime=getMilliSecSince(time);
    emit workingTimeChanged();
}

void Calibrate::removeDir()
{
    QDir dir(tempDir);
    if (dir.exists()) dir.removeRecursively();
}

bool Calibrate::reloadDir()
{
    removeDir();
    return QDir(tempDir).mkdir(tempDir);
}

QStringList Calibrate::toString(cv::Mat mat)
{
    QStringList result;
    for (int i=0; i<mat.rows; i++) {
        QString ss;
        for (int j=0; j<mat.cols; j++)
            ss+=" "+QString::number(mat.at<double>(i,j));
        result.push_back(ss);
    }
    return result;
}
