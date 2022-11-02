import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Dialogs 1.3

import "qrc:/QML/ElementBase"
import "qrc:/QML/CardBase"
import "qrc:/QML"

Rectangle{
    color: Style.currentTheme.primary

    signal openFileDialog()
    signal startCalibrate()

    FileDialog {
        id: saveDialog
        title: "Сохранить результаты калибровки камеры"
        nameFilters: [ "XML files (*.xml)"  ]
        selectExisting: false
        onAccepted: {
            calibrate.save(fileUrl)
        }
    }

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

            ButtonCard{
                iconSource:"qrc:/ASSETS/icon/play.svg"
                labelText:  "Начать калибровку"
                onClicked: startCalibrate()
            }    

            MTK_HSeparator{}

            InfoCard{
                infoText: calibrate.workingTime
                labelText: "время работы,сек"
            }

            InfoCard{
                infoText: calibrate.inputFrames
                labelText: "выбрано для обработки кадров"
            }

            InfoCard{
                infoText: calibrate.successFrame
                labelText: "успешно обработано кадров"
            }

            InfoCard{
                infoText: calibrate.errorRMS.toFixed(3)
                labelText: "СКО повторного проецирования"
            }

            MTK_HSeparator{}

            MTK_Label{
                text: "Матрица внутренних параметров камеры"
                anchors.left: parent.left
                anchors.leftMargin: Style.panelsMargins*2
                horizontalAlignment: Text.AlignLeft
                height: Style.cardHeight
                color: Style.currentTheme.accent
            }

            MTK_HSeparator{}

            MatTableCard{
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: Style.panelsMargins
                model: calibrate.getCameraModel()
            }

            MTK_HSeparator{}

            MTK_Label{
                text: "Матрица коэффициентов искажений"
                anchors.left: parent.left
                anchors.leftMargin: Style.panelsMargins*2
                horizontalAlignment: Text.AlignLeft
                height: Style.cardHeight
                color: Style.currentTheme.accent
            }

            MTK_HSeparator{}

            MatTableCard{
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: Style.panelsMargins
                model: calibrate.getDistModel()
            }

           MTK_HSeparator{}

            ButtonCard{
                iconSource:"qrc:/ASSETS/icon/save.svg"
                labelText:  "Сохранить результаты"
                onClicked: saveDialog.open()
            }

            MTK_HSeparator{}
        }
    }
}
