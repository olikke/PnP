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

    Q_PROPERTY(bool getDarkTheme READ getDarkTheme WRITE setDarkTheme NOTIFY darkThemeChanged)
    bool getDarkTheme() {return m_darkTheme;}
    void setDarkTheme(bool val) {m_darkTheme = val;}

    Q_PROPERTY(int x READ getX WRITE setX NOTIFY xChanged)
    int getX() {return x;}
    void setX(int val){x=val;}

    Q_PROPERTY(int y READ getY WRITE setY NOTIFY yChanged)
    int getY() {return y;}
    void setY(int val){y=val;}

    Q_PROPERTY(int frameWidth READ getFrameWidth WRITE setFrameWidth NOTIFY frameWidthChanged)
    int getFrameWidth() {return m_frameWidth;}
    void setFrameWidth(int val) {m_frameWidth=val;}

    Q_PROPERTY(int frameHeight READ getFrameHeight WRITE setFrameHeight NOTIFY frameHeightChanged)
    int getFrameHeight() {return m_frameHeight;}
    void setFrameHeight(int val) {m_frameHeight=val;}

    Q_PROPERTY(int borderWidth READ getBorderWidth WRITE setBorderWidth NOTIFY borderWidthChanged)
    int getBorderWidth() {return m_borderWidth;}
    void setBorderWidth(int val) {m_borderWidth=val;}

    Q_PROPERTY(int borderHeight READ getBoderHeight WRITE setBorderHeight NOTIFY borderHeightChanged)
    int getBoderHeight() {return m_borderHeight;}
    void setBorderHeight(int val) {m_borderHeight=val;}

    Q_PROPERTY(int squareSize READ getSquareSize WRITE setSquareSize NOTIFY squareSizeChanged)
    int getSquareSize() {return m_squareSize;}
    void setSquareSize(int val) {m_squareSize=val;}

signals:
    void darkThemeChanged(bool val);
    void xChanged(int val);
    void yChanged(int val);
    void frameWidthChanged(int val);
    void frameHeightChanged(int val);
    void borderWidthChanged(int val);
    void borderHeightChanged(int val);
    void squareSizeChanged(float value);
private:
    QSettings qsettings;
    bool m_darkTheme;
    int x=0;
    int y=0;
    int m_frameWidth=1920;
    int m_frameHeight=1080;
    int m_borderWidth=7;
    int m_borderHeight=5;
    int m_squareSize=20;
private:
    bool loadConfig();
    void writeConfig();
};
