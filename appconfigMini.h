#pragma once

#include <QObject>
#include <QSettings>
#include <QTextCodec>
#include <QFile>

class AppConfigMini : public QObject
{
    Q_OBJECT

public:
    AppConfigMini(QObject *parent = nullptr,QString filename = "config-PnP");
    ~AppConfigMini();

    Q_PROPERTY(bool darkTheme READ darkTheme WRITE setDarkTheme NOTIFY darkThemeChanged)
    bool darkTheme() const;
    void setDarkTheme(bool darkTheme);

    Q_PROPERTY(int x READ getX WRITE setX NOTIFY xChanged)
    int getX() const {return x;}
    void setX(int xx);

    Q_PROPERTY(int y READ getY WRITE setY NOTIFY yChanged)
    int getY() const {return y;}
    void setY(int yy);

    Q_PROPERTY(int frameWidth READ frameWidth NOTIFY widthChanged)
    int frameWidth() const {return width;}

    Q_PROPERTY(int frameHeight READ frameHeight NOTIFY heightChanged)
    int frameHeight() const {return height;}

signals:
    void darkThemeChanged(bool val);
    void xChanged(int val);
    void yChanged(int val);
    void widthChanged(int val);
    void heightChanged(int val);
private:
    QSettings qsettings;
    bool m_darkTheme;
    int x=0;
    int y=0;
    int width=1920;
    int height=1080;
private:
    bool loadConfig();
    void writeConfig();
};
