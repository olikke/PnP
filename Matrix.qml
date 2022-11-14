import QtQuick 2.0
import QtQuick.Dialogs 1.3

import "qrc:/QML"
import "qrc:/QML/ElementBase"
import "qrc:/QML/CardBase"

Rectangle{
    color: Style.currentTheme.primary
    anchors.fill: parent

    FileDialog {
        id: openXML
        title: "Открыть результаты калибровки камеры"
        nameFilters: [ "XML files (*.xml)"  ]
        onAccepted: {
            matManager.openMatrix(fileUrl)
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

            MTK_Label{
                text: "матрицы калибровки и искажений камеры"
                anchors.left: parent.left
                anchors.leftMargin: Style.panelsMargins*2
                horizontalAlignment: Text.AlignLeft
                height: Style.cardHeight
                color: Style.currentTheme.accent
            }

            MTK_HSeparator{}

            ButtonCard{
                iconSource:"qrc:/ASSETS/icon/matrix.svg"
                labelText:  "Загрузить параметры камеры"
                onClicked: openXML.open()
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
                model: matManager.getCameraModel()
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
                model: matManager.getDistModel()
            }

           MTK_HSeparator{}

        }
    }
}
