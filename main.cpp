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
#include "docking.h"
#include "matrixmanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();

    AppConfigMini* appConfig=new AppConfigMini(&app);
    context->setContextProperty("appConfig",appConfig);

    MatrixManager* matManager= new MatrixManager(appConfig, &app);
    context->setContextProperty("matManager",matManager);

    ImageProvider* videoProvider = new ImageProvider(&app,QSize(appConfig->getFrameWidth(),appConfig->getFrameHeight()));
    context->setContextProperty("videoProvider",videoProvider);
    engine.addImageProvider("mlive",videoProvider);

    CamFinder* camFinder=new CamFinder(&app);
    context->setContextProperty("camFinder",camFinder);

    GrabOpenCV* grabber=new GrabOpenCV(matManager,&app,appConfig->getFrameWidth(),appConfig->getFrameHeight());
    context->setContextProperty("grabber",grabber);

    QObject::connect(grabber,&GrabOpenCV::newFrame,videoProvider,&ImageProvider::updateImage);

    FolderBackend* folderBack=new FolderBackend(&app);
    context->setContextProperty("folderBack",folderBack);

    Calibrate* calibrate=new Calibrate(appConfig,matManager,&app);
    context->setContextProperty("calibrate",calibrate);

    PnP* pnp=new PnP(appConfig,matManager,&app);
    context->setContextProperty("pnp",pnp);

    ImageProvider* pnpProvider = new ImageProvider(&app,QSize(appConfig->getFrameWidth(),appConfig->getFrameHeight()));
    context->setContextProperty("pnpProvider",pnpProvider);
    engine.addImageProvider("plive",pnpProvider);

    QObject::connect(pnp,&PnP::newFrame,pnpProvider,&ImageProvider::updateImage);
    QObject::connect(appConfig,&AppConfigMini::squareSizeChanged,pnp,&PnP::squareSizeChanged);

    Docking* docking=new Docking(appConfig,matManager,&app);
    context->setContextProperty("docking",docking);

    ImageProvider* dockProvider = new ImageProvider(&app,QSize(appConfig->getFrameWidth(),appConfig->getFrameHeight()));
    context->setContextProperty("dockProvider",dockProvider);
    engine.addImageProvider("dlive",dockProvider);

    QObject::connect(docking,&Docking::newFrame,dockProvider,&ImageProvider::updateImage);


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())  return -1;

    return app.exec();
}
