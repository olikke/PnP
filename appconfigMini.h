#pragma once

#include <QObject>
#include <QSettings>
#include <QTextCodec>
#include <QFile>

class AppConfigMini : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool darkTheme READ darkTheme WRITE setDarkTheme NOTIFY darkThemeChanged)
    Q_PROPERTY(int x READ getX WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ getY WRITE setY NOTIFY yChanged)

public:
    AppConfigMini(QObject *parent = nullptr,QString filename = "appConfig");

    bool darkTheme() const;
    void setDarkTheme(bool darkTheme);

    int getX() const {return x;}
    void setX(int xx);

    int getY() const {return y;}
    void setY(int yy);
private:
    QString filename;
    bool m_darkTheme;
    int x=0;
    int y=0;
signals:
    void darkThemeChanged(bool darkTheme);
    void xChanged(int x);
    void yChanged(int y);
private:
    bool loadConfig();
    void writeConfig();
};
