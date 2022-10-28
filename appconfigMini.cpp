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

bool AppConfigMini::darkTheme() const
{
    return m_darkTheme;
}

void AppConfigMini::setDarkTheme(bool darkTheme)
{
    m_darkTheme = darkTheme;
    emit darkThemeChanged(m_darkTheme);
}

void AppConfigMini::setX(int xx)
{
    x=xx;
    emit xChanged(x);    
}

void AppConfigMini::setY(int yy)
{
    y=yy;
    emit yChanged(y);
}

bool AppConfigMini::loadConfig()
{
    if(QFile::exists(qsettings.fileName())){
        qsettings.beginGroup("General");
        m_darkTheme = qsettings.value("darktheme").toBool();
        x=qsettings.value("x",0).toInt();
        y=qsettings.value("y",0).toInt();
        width=qsettings.value("frameWidth_pixel",1920).toInt();
        height=qsettings.value("frameHeight_pixel",1080).toInt();
        bWidth=qsettings.value("borderWidth",7).toInt();
        bHeight=qsettings.value("borderHeight",5).toInt();
        sSizeMM=qsettings.value("squareSize_mm",20).toInt();
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
    qsettings.setValue("frameWidth_pixel",width);
    qsettings.setValue("frameHeight_pixel",height);
    qsettings.setValue("borderWidth",bWidth);
    qsettings.setValue("borderHeight",bHeight);
    qsettings.setValue("squareSize_mm",sSizeMM);
    qsettings.endGroup();
}
