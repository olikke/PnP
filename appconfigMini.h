#pragma once

#include <QObject>
#include <QSettings>
#include <QTextCodec>
#include <QFile>
#include <QDebug>

class AppConfigMini : public QObject
{
    Q_OBJECT

public:
    AppConfigMini(QObject *parent = nullptr,QString filename = "config-PnP");
    ~AppConfigMini();

    Q_PROPERTY(bool getDarkTheme READ getDarkTheme WRITE setDarkTheme NOTIFY darkThemeChanged)
    bool getDarkTheme() {return m_darkTheme;}
    void setDarkTheme(bool val) {m_darkTheme = val; emit darkThemeChanged(val);}

    Q_PROPERTY(int x READ getX WRITE setX NOTIFY xChanged)
    int getX() {return x;}
    void setX(int val){x=val; emit xChanged(val);}

    Q_PROPERTY(int y READ getY WRITE setY NOTIFY yChanged)
    int getY() {return y;}
    void setY(int val){y=val; emit yChanged(val);}

    Q_PROPERTY(int frameWidth READ getFrameWidth WRITE setFrameWidth NOTIFY frameWidthChanged)
    int getFrameWidth() {return m_frameWidth;}
    void setFrameWidth(int val) {m_frameWidth=val; emit frameWidthChanged(val);}

    Q_PROPERTY(int frameHeight READ getFrameHeight WRITE setFrameHeight NOTIFY frameHeightChanged)
    int getFrameHeight() {return m_frameHeight;}
    void setFrameHeight(int val) {m_frameHeight=val; emit frameHeightChanged(val);}

    Q_PROPERTY(int borderWidth READ getBorderWidth WRITE setBorderWidth NOTIFY borderWidthChanged)
    int getBorderWidth() {return m_borderWidth;}
    void setBorderWidth(int val) {m_borderWidth=val; emit borderWidthChanged(val);}

    Q_PROPERTY(int borderHeight READ getBoderHeight WRITE setBorderHeight NOTIFY borderHeightChanged)
    int getBoderHeight() {return m_borderHeight;}
    void setBorderHeight(int val) {m_borderHeight=val; emit borderHeightChanged(val);}

    Q_PROPERTY(int squareSize READ getSquareSize WRITE setSquareSize NOTIFY squareSizeChanged)
    int getSquareSize() {return m_squareSize;}
    void setSquareSize(int val) {m_squareSize=val; emit squareSizeChanged(val);}

    //кол-во итераций поиска субпикселей углов
    Q_PROPERTY(int iterations READ getIterations WRITE setIterations NOTIFY iterationsChanged)
    int getIterations() {return m_iterations;}
    void setIterations(int val) {m_iterations=val; emit iterationsChanged(val);}

    //точность поиска субпикселей углов
    Q_PROPERTY(double epsilon READ getEpsilon WRITE setEpsilon NOTIFY epsilonChanged)
    double getEpsilon() {return m_epsilon;}
    void setEpsilon(double val) {m_epsilon=val; emit epsilonChanged(val);}

    Q_PROPERTY(int epsilonDivider READ getEpsilonDivider CONSTANT)
    int getEpsilonDivider() {return qRound(m_epsilonDivider);}

    Q_PROPERTY(QString matrixFileName READ getMatrixFileName WRITE setMatrixFileName)
    QString getMatrixFileName() {return m_fileName;}
    void setMatrixFileName(QString val) {m_fileName=val;}

signals:
    void darkThemeChanged(bool);
    void xChanged(int);
    void yChanged(int);
    void frameWidthChanged(int);
    void frameHeightChanged(int);
    void borderWidthChanged(int);
    void borderHeightChanged(int);
    void squareSizeChanged(float);
    void iterationsChanged(int);
    void epsilonChanged(double);
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
    int m_iterations=30;
    double m_epsilon=0.1;
    double m_epsilonDivider=100.;
    QString m_fileName="";
private:
    bool loadConfig();
    void writeConfig();
};
