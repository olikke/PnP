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
#include "framemodel.h"

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

    ImageProvider* provider = new ImageProvider(&app);
    context->setContextProperty("videoProvider",provider);
    engine->addImageProvider("mlive",provider);

    AppConfigMini* appConfig=new AppConfigMini(&app);
    context->setContextProperty("appConfig",appConfig);

    FrameModel* frameModel=new FrameModel(&app);
    context->setContextProperty("frameModel",frameModel);

    engine->load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine->rootObjects().isEmpty())  return -1;

    return app.exec();
}
