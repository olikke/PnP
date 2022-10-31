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

            MTK_Label{
                text: "Настройки"
                anchors.left: parent.left
                anchors.leftMargin: Style.panelsMargins*2
                horizontalAlignment: Text.AlignLeft
                color: Style.currentTheme.accent
            }

            SliderCard{
                labelText: "Ширина кадра, пикс"
                from: 720
                to: 2048
                value: appConfig.frameWidth
                stepSize: 4
                onMove: appConfig.frameWidth=value
            }

            SliderCard{
                labelText: "Высота кадра, пикс"
                from: 576
                to: 2048
                value: appConfig.frameHeight
                stepSize: 4
                onMove: appConfig.frameHeight=value
            }

            SliderCard{
                labelText: "Ширина доски, шт"
                from: 1
                to: 13
                value: appConfig.borderWidth
                stepSize: 1
                onMove: appConfig.borderWidth=value
            }

            SliderCard{
                labelText: "Высота доски, шт"
                from: 1
                to: 13
                value: appConfig.borderHeight
                stepSize: 1
                onMove: appConfig.borderHeight=value
            }

            SliderCard{
                labelText: "Сторона квадрата, мм"
                from: 1
                to: 50
                value: appConfig.squareSize
                stepSize: 1
                onMove: appConfig.squareSize=value
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
                to: 100
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
                model: calibrate.getCameraModel()
            }

            MTK_Label{
                text: "Матрица коэффициентов искажений"
                anchors.left: parent.left
                anchors.leftMargin: Style.panelsMargins*2
                horizontalAlignment: Text.AlignLeft
            }

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
