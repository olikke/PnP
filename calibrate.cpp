#include "calibrate.h"

Calibrate::Calibrate(AppConfigMini* appConfig,QObject *parent) :
    QObject(parent),
    m_appConfig(appConfig),
    cameraMatrix(cv::Mat(3,3,CV_64FC1)),
    cameraModel(new MatModel(&cameraMatrix,this)),
    distMatrix(cv::Mat(1,5,CV_64FC1)),
    distModel(new MatModel(&distMatrix,this)),
    tempDir(QCoreApplication::applicationDirPath()+"/.temporary/")
{
    if (!reloadDir()) qDebug()<<"Не удалось создать папку для временных файлов";
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
    if (s!=newTask.frameSize) return newTask;
   // const cv::Point3f kCenterOffset((newTask.boardSize.width - 1) * newTask.squareSize, (newTask.boardSize.height - 1) * newTask.squareSize, 0.f);
    cv::cvtColor(frame,frame,CV_BGR2GRAY);
    newTask.success=cv::findChessboardCorners(frame,newTask.boardSize,newTask.corners);
    if (newTask.success) {
        //olikke cv::Size(11,11) зона поиска - изменение/производительность/точность
        // cv::Size(-1,-1) мёртвая зона
        cv::cornerSubPix(frame,newTask.corners,cv::Size(9,9),cv::Size(-1,-1),newTask.criteria);
        cv::cvtColor(frame,frame,CV_GRAY2BGR);
        cv::drawChessboardCorners(frame,newTask.boardSize,newTask.corners,newTask.success);
        for (int i=0; i<newTask.boardSize.height; i++)
            for (int j=0; j<newTask.boardSize.width;j++)
                newTask.object.push_back(cv::Point3f(j*task.squareSize,i*task.squareSize,0)/*-kCenterOffset*/);
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
    cv::Size m_boardSize=cv::Size(m_appConfig->getBorderWidth(),m_appConfig->getBoderHeight());
    float m_squareSize=m_appConfig->getSquareSize();
    cv::Size m_frameSize=cv::Size(m_appConfig->getFrameWidth(),m_appConfig->getFrameHeight());
    cv::vector<cv::vector<cv::Point3f>> objPoints; //координаты углов в пространстве
    cv::vector<cv::vector<cv::Point2f>> imgPoints; //координаты углов на изображении (найденные с субпиксельной точностью)
    std::chrono::high_resolution_clock::time_point time;
    getTime(time);
    QDir source(QUrl(url).toLocalFile());
    QStringList list = source.entryList(QDir::Files | QDir::AllEntries | QDir::NoDotAndDotDot);
    m_inputFrames=list.count();
    inputFramesChanged();
    QList<Task> blank;
    cv::TermCriteria criteria=cv::TermCriteria(CV_TERMCRIT_EPS+CV_TERMCRIT_ITER,m_appConfig->getIterations(),m_appConfig->getEpsilon());
    for (QString fn: list) {
        if (!fileName.contains(fn)) continue;
        QFile::copy(QUrl(url).toLocalFile()+"/"+fn, tempDir+fn);
        Task task;
        task.fileName=tempDir+fn;
        task.squareSize=m_squareSize;
        task.boardSize=m_boardSize;
        task.frameSize=m_frameSize;
        task.criteria=criteria;
        task.success=false;
        blank.push_back(task);        
    }
    QList<Task> result=QtConcurrent::blockingMapped(blank,calc);
    m_succesFrame=0;
    for (Task task:result) {
        if (!task.success) continue;
        m_succesFrame++;
        objPoints.push_back(task.object);
        imgPoints.push_back(task.corners);
    }
    emit successFrameChanged();
    if (m_succesFrame==0) {
        m_errorRMS=0;
        emit errorRMSChanged();
        m_workingTime=getMilliSecSince(time);
        emit workingTimeChanged();
        cameraMatrix=cv::Mat::zeros(cameraMatrix.rows,cameraMatrix.cols,cameraMatrix.type());
        cameraModel->update();
        distMatrix=cv::Mat::zeros(distMatrix.rows,distMatrix.cols,distMatrix.type());
        distModel->update();
        return;
    }
    //https://stackoverflow-com.translate.goog/questions/53277597/fundamental-understanding-of-tvecs-rvecs-in-opencv-aruco?_x_tr_sl=en&_x_tr_tl=ru&_x_tr_hl=ru&_x_tr_pto=sc
    cv::_OutputArray rotation;
    cv::_OutputArray translation;
    int flags =  cv::CALIB_FIX_PRINCIPAL_POINT;// | cv::CALIB_RATIONAL_MODEL;
    m_errorRMS=cv::calibrateCamera(objPoints,imgPoints,m_frameSize,cameraMatrix,distMatrix,rotation,translation,flags,criteria);
    emit errorRMSChanged();
    cameraModel->update();
    distModel->update();
    m_workingTime=getMilliSecSince(time);
    emit workingTimeChanged();
}


void Calibrate::save(QString url)
{
    cv::FileStorage fs(QUrl(url).toLocalFile().toLatin1().constData(), cv::FileStorage::WRITE);
    fs<<"CameraMatrix"<<cameraMatrix;
    fs<<"DistorsionMatrix"<<distMatrix;
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
