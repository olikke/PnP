#ifdef QT_WIDGETS_LIB
#include <QtWidgets/QApplication>
#else
#include <QtGui/QGuiApplication>
#endif
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>

#include "calibration.h"
#include "imageprovider.h"
#include "appconfigMini.h"
#include "camfinder.h"
#include "grabopencv.h"

int main(int argc, char *argv[])
{
#ifdef QT_WIDGETS_LIB
    QApplication app(argc, argv);
#else
    QGuiApplication app(argc, argv);
#endif

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setApplicationName(QStringLiteral("Photosurface"));
    QCoreApplication::setOrganizationName(QStringLiteral("QtProject"));

    QQmlApplicationEngine * engine=new QQmlApplicationEngine(&app);
    QQmlContext *context = engine->rootContext();

    int width=1920;
    int height=1200;

    ImageProvider* provider = new ImageProvider(&app,QSize(width,height));
    context->setContextProperty("videoProvider",provider);
    engine->addImageProvider("mlive",provider);

    AppConfigMini* appConfig=new AppConfigMini(&app);
    context->setContextProperty("appConfig",appConfig);

    context->setContextProperty("frameWidth",width);
    context->setContextProperty("frameHeight",height);

    CamFinder* camFinder=new CamFinder(&app);
    context->setContextProperty("camFinder",camFinder);

    GrabOpenCV* grabber=new GrabOpenCV(&app,width,height);
    context->setContextProperty("grabber",grabber);

    QObject::connect(grabber,&GrabOpenCV::newFrame,provider,&ImageProvider::updateImage);

    engine->load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine->rootObjects().isEmpty())  return -1;

    return app.exec();
}
