#include "appconfigMini.h"

AppConfigMini::AppConfigMini(QObject *parent, QString filename):
    QObject (parent),
    qsettings(QSettings::IniFormat, QSettings::UserScope, filename),
    m_darkTheme(true)
{
   qsettings.setIniCodec(QTextCodec::codecForName("UTF-8"));
   if(!loadConfig()) writeConfig();
}

AppConfigMini::~AppConfigMini()
{
    writeConfig();
}

bool AppConfigMini::loadConfig()
{
    if(QFile::exists(qsettings.fileName())){
        qsettings.beginGroup("General");
        m_darkTheme = qsettings.value("darktheme").toBool();
        x=qsettings.value("x",0).toInt();
        y=qsettings.value("y",0).toInt();
        m_frameWidth=qsettings.value("frameWidth_pixel",1920).toInt();
        m_frameHeight=qsettings.value("frameHeight_pixel",1080).toInt();
        m_borderWidth=qsettings.value("borderWidth",7).toInt();
        m_borderHeight=qsettings.value("borderHeight",5).toInt();
        m_squareSize=qsettings.value("squareSize_mm",20).toInt();
        m_epsilon=qsettings.value("epsilon",0.1).toDouble();
        m_iterations=qsettings.value("iterations",30).toInt();
        qsettings.endGroup();
        return true;
    }
    return false;
}

void AppConfigMini::writeConfig()
{
    qsettings.beginGroup("General");
    qsettings.setValue("darktheme", m_darkTheme);
    qsettings.setValue("x",x);
    qsettings.setValue("y",y);
    qsettings.setValue("frameWidth_pixel",m_frameWidth);
    qsettings.setValue("frameHeight_pixel",m_frameHeight);
    qsettings.setValue("borderWidth",m_borderWidth);
    qsettings.setValue("borderHeight",m_borderHeight);
    qsettings.setValue("squareSize_mm",m_squareSize);
    qsettings.setValue("epsilon",m_epsilon);
    qsettings.setValue("iterations",m_iterations);
    qsettings.endGroup();
}
