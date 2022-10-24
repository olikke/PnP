#include "appconfigMini.h"

AppConfigMini::AppConfigMini(QObject *parent, QString filename):
    QObject (parent),
    filename(filename),
    m_darkTheme(true)
{
    if(!loadConfig()) writeConfig();
}

bool AppConfigMini::darkTheme() const
{
    return m_darkTheme;
}

void AppConfigMini::setDarkTheme(bool darkTheme)
{
    m_darkTheme = darkTheme;
    emit darkThemeChanged(m_darkTheme);
    writeConfig();
}

void AppConfigMini::setX(int xx)
{
    x=xx;
    emit xChanged(x);
    writeConfig();
}

void AppConfigMini::setY(int yy)
{
    y=yy;
    emit yChanged(y);
    writeConfig();
}

bool AppConfigMini::loadConfig()
{
    QSettings qsettings(QSettings::IniFormat, QSettings::UserScope, filename);
    qsettings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    if(QFile::exists(qsettings.fileName())){
        qsettings.beginGroup("General");
        m_darkTheme = qsettings.value("darktheme").toBool();
        x=qsettings.value("x",0).toInt();
        y=qsettings.value("y",0).toInt();
        qsettings.endGroup();
        return true;
    }
    return false;
}

void AppConfigMini::writeConfig()
{
    QSettings qsettings(QSettings::IniFormat, QSettings::UserScope, filename);
    qsettings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    qsettings.beginGroup("General");
    qsettings.setValue("darktheme", m_darkTheme);
    qsettings.setValue("x",x);
    qsettings.setValue("y",y);
    qsettings.endGroup();
}
