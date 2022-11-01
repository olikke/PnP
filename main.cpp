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
#include "pnp.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();

    AppConfigMini* appConfig=new AppConfigMini(&app);
    context->setContextProperty("appConfig",appConfig);

    ImageProvider* videoProvider = new ImageProvider(&app,QSize(appConfig->getFrameWidth(),appConfig->getFrameHeight()));
    context->setContextProperty("videoProvider",videoProvider);
    engine.addImageProvider("mlive",videoProvider);

    CamFinder* camFinder=new CamFinder(&app);
    context->setContextProperty("camFinder",camFinder);

    GrabOpenCV* grabber=new GrabOpenCV(&app,appConfig->getFrameWidth(),appConfig->getFrameHeight());
    context->setContextProperty("grabber",grabber);

    QObject::connect(grabber,&GrabOpenCV::newFrame,videoProvider,&ImageProvider::updateImage);

    FolderBackend* folderBack=new FolderBackend(&app);
    context->setContextProperty("folderBack",folderBack);

    Calibrate* calibrate=new Calibrate(&app,appConfig);
    context->setContextProperty("calibrate",calibrate);

    PnP* pnp=new PnP(&app);
    context->setContextProperty("pnpos",pnp);

    ImageProvider* pnpProvider = new ImageProvider(&app);
    context->setContextProperty("pnpProvider",pnpProvider);
    engine.addImageProvider("plive",pnpProvider);

    QObject::connect(pnp,&PnP::newFrame,pnpProvider,&ImageProvider::updateImage);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())  return -1;

    return app.exec();
}
