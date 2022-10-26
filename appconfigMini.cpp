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
        width=qsettings.value("frameWidth",1920).toInt();
        height=qsettings.value("frameHeight",1080).toInt();
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
    qsettings.setValue("frameWidth",width);
    qsettings.setValue("frameHeight",height);
    qsettings.endGroup();
}
