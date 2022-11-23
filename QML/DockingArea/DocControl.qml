import QtQuick 2.0

import "qrc:/QML/ElementBase"
import "qrc:/QML/CardBase"
import "qrc:/QML"

Rectangle{
    color: Style.currentTheme.primary

    signal openImageDialog()

    Flickable {
        id: root
        anchors.fill: parent
        flickableDirection: Flickable.VerticalFlick
        contentHeight: control.height+60

        Column {
            id: control
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            spacing: Style.connectionWidth

            ButtonCard{
                iconSource:"qrc:/ASSETS/icon/folder.svg"
                labelText:  "Выбрать изображение"
                onClicked: openImageDialog()
            }

            MTK_HSeparator{}

            ButtonCard{
                iconSource:"qrc:/ASSETS/icon/circle.svg"
                labelText:  "Найти цель"
                onClicked: docking.findCircle()
            }

            MTK_HSeparator{}

            SliderCard{
                labelText: "Порог"
                from: 0
                to: 255
                value: docking.threshold
                stepSize: 1
                onMove: docking.threshold=value
            }

            MTK_HSeparator{}

        }

    }
}
