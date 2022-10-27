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

            Item{
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: Style.panelsMargins
                height: Style.cardHeight/2
                MTK_Label{
                    id: l1
                    text: "Поиск углов"
                    anchors.left: parent.left
                    horizontalAlignment: Text.AlignLeft
                    color: Style.currentTheme.accent
                }
                MTK_Label{
                    text: "время выполнения "+calibrate.timeFindCorners.toFixed(3)+" с"
                    opacity: 0.4
                    anchors.right: parent.right
                    horizontalAlignment: Text.AlignRight
                }
            }

            ButtonCard{
                iconSource:"qrc:/ASSETS/icon/play.svg"
                labelText:  "Начать поиск"
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
        }
    }
}
