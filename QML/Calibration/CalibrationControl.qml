import QtQuick 2.0
import QtQuick.Controls 2.4

import "qrc:/QML/ElementBase"
import "qrc:/QML/CardBase"
import "qrc:/QML"

Rectangle{
    color: Style.currentTheme.primary

    signal openFileDialog()
    signal startCalibrate()

    Flickable {
        id: root
        anchors.fill: parent
        flickableDirection: Flickable.VerticalFlick
        contentHeight: control.height

        Column {
            id: control
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            spacing: Style.connectionWidth

            ButtonCard{
                iconSource:"qrc:/ASSETS/icon/folder.svg"
                labelText:  folderModel.folder!=""? folderModel.folder :"Выбрать изображения"
                onClicked: openFileDialog()
            }

            MTK_HSeparator{}

            MTK_Label{
                text: "Калибровка"
                anchors.left: parent.left
                anchors.leftMargin: Style.panelsMargins*2
                horizontalAlignment: Text.AlignLeft
                color: Style.currentTheme.accent
            }

            ButtonCard{
                iconSource:"qrc:/ASSETS/icon/play.svg"
                labelText:  "Начать калибровку"
                onClicked: startCalibrate()
            }

            SliderCard{
                labelText: "Количество итерраций"
                from: 10
                to: 50
                value: calibrate.iterations
                stepSize: 1
                onMove: calibrate.iterations=value
            }

            SliderCard{
                labelText: "Точность приближения"
                from: 1
                to: 50
                value: calibrate.epsilon
                stepSize: 1
                onMove: calibrate.epsilon=value
                divider: calibrate.epsilonDivider
            }            

            MTK_HSeparator{}

            MTK_Label{
                text: "Результаты"
                anchors.left: parent.left
                anchors.leftMargin: Style.panelsMargins*2
                horizontalAlignment: Text.AlignLeft
                color: Style.currentTheme.accent
            }

            InfoCard{
                infoText: calibrate.workingTime
                labelText: "время работы,сек"
            }

            InfoCard{
                infoText: calibrate.successFrame
                labelText: "успешно обработано кадров"
            }

            InfoCard{
                infoText: calibrate.errorRMS.toFixed(3)
                labelText: "СКО повторного проецирования"
            }

            MTK_Label{
                text: "Матрица внутренних параметров камеры"
                anchors.left: parent.left
                anchors.leftMargin: Style.panelsMargins*2
                horizontalAlignment: Text.AlignLeft
            }

            MatTableCard{
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: Style.panelsMargins
                model: calibrate.getCameraMatrix()
            }

            Row{
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: Style.panelsMargins
                height: Style.btnHeight*0.8
                spacing: Style.connectionWidth
                MTK_FramedLabel{
                    text: calibrate.timeFindCorners
                    width: parent.width/3-parent.spacing*2/3
                    height: parent.height
                    border.color: Style.currentTheme.background
                    radius: Style.unitRadius
                    color: border.color
                }
                MTK_FramedLabel{
                    text: calibrate.timeFindCorners
                    width: parent.width/3-parent.spacing*2/3
                    height: parent.height
                    border.color: Style.currentTheme.background
                    radius: Style.unitRadius
                    color: border.color
                }
                MTK_FramedLabel{
                    text: calibrate.timeFindCorners
                    width: parent.width/3-parent.spacing*2/3
                    height: parent.height
                    border.color: Style.currentTheme.background
                   radius: Style.unitRadius
                   color: border.color
                }
            }

            Row{
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: Style.panelsMargins
                height: Style.btnHeight*0.8
                spacing: Style.connectionWidth
                MTK_FramedLabel{
                    text: calibrate.timeFindCorners
                    width: parent.width/3-parent.spacing*2/3
                    height: parent.height
                    border.color: Style.currentTheme.background
                    radius: Style.unitRadius
                    color: border.color
                }
                MTK_FramedLabel{
                    text: calibrate.timeFindCorners
                    width: parent.width/3-parent.spacing*2/3
                    height: parent.height
                    border.color: Style.currentTheme.background
                    radius: Style.unitRadius
                    color: border.color
                }
                MTK_FramedLabel{
                    text: calibrate.timeFindCorners
                    width: parent.width/3-parent.spacing*2/3
                    height: parent.height
                    border.color: Style.currentTheme.background
                   radius: Style.unitRadius
                   color: border.color
                }
            }

            Row{
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: Style.panelsMargins
                height: Style.btnHeight*0.8
                spacing: Style.connectionWidth
                MTK_FramedLabel{
                    text: calibrate.timeFindCorners
                    width: parent.width/3-parent.spacing*2/3
                    height: parent.height
                    border.color: Style.currentTheme.background
                    radius: Style.unitRadius
                    color: border.color
                }
                MTK_FramedLabel{
                    text: calibrate.timeFindCorners
                    width: parent.width/3-parent.spacing*2/3
                    height: parent.height
                    border.color: Style.currentTheme.background
                    radius: Style.unitRadius
                    color: border.color
                }
                MTK_FramedLabel{
                    text: calibrate.timeFindCorners
                    width: parent.width/3-parent.spacing*2/3
                    height: parent.height
                    border.color: Style.currentTheme.background
                    radius: Style.unitRadius
                    color: border.color
                }
            }

            MTK_Label{
                text: "Матрица коэффициентов искажений"
                anchors.left: parent.left
                anchors.leftMargin: Style.panelsMargins*2
                horizontalAlignment: Text.AlignLeft
            }


            MTK_HSeparator{}
        }
    }
}
