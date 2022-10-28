#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>

#include "imageprovider.h"
#include "appconfigMini.h"
#include "camfinder.h"
#include "grabopencv.h"
#include "folderBackend.h"
#include "calibrate.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QQmlApplicationEngine * engine=new QQmlApplicationEngine(&app);
    QQmlContext *context = engine->rootContext();

    AppConfigMini* appConfig=new AppConfigMini(&app);
    context->setContextProperty("appConfig",appConfig);

    ImageProvider* provider = new ImageProvider(&app,QSize(appConfig->frameWidth(),appConfig->frameHeight()));
    context->setContextProperty("videoProvider",provider);
    engine->addImageProvider("mlive",provider);

    CamFinder* camFinder=new CamFinder(&app);
    context->setContextProperty("camFinder",camFinder);

    GrabOpenCV* grabber=new GrabOpenCV(&app,appConfig->frameWidth(),appConfig->frameHeight());
    context->setContextProperty("grabber",grabber);

    QObject::connect(grabber,&GrabOpenCV::newFrame,provider,&ImageProvider::updateImage);

    FolderBackend* folderBack=new FolderBackend(&app);
    context->setContextProperty("folderBack",folderBack);

    Calibrate* calibrate=new Calibrate(&app,appConfig->borderWidth(),appConfig->borderHeight(),appConfig->squareSizeMM());
    context->setContextProperty("calibrate",calibrate);

    engine->load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine->rootObjects().isEmpty())  return -1;

    return app.exec();
}
