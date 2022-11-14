import QtQuick 2.0

import "qrc:/QML"
import "qrc:/QML/ElementBase"
import "qrc:/QML/CardBase"

Rectangle{
    color: Style.currentTheme.primary
    anchors.fill: parent

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
                text: "Настройки камеры/изображений"
                anchors.left: parent.left
                anchors.leftMargin: Style.panelsMargins*2
                horizontalAlignment: Text.AlignLeft
                height: Style.cardHeight
                color: Style.currentTheme.accent
            }

            MTK_HSeparator{}

            SliderCard{
                labelText: "Ширина кадра, пикс"
                from: 640
                to: 2048
                value: appConfig.frameWidth
                stepSize: 4
                onMove: appConfig.frameWidth=value
            }

            SliderCard{
                labelText: "Высота кадра, пикс"
                from: 480
                to: 2048
                value: appConfig.frameHeight
                stepSize: 4
                onMove: appConfig.frameHeight=value
            }

            MTK_HSeparator{}

            MTK_Label{
                text: "Параметры калибровочной доски"
                anchors.left: parent.left
                anchors.leftMargin: Style.panelsMargins*2
                horizontalAlignment: Text.AlignLeft
                height: Style.cardHeight
                color: Style.currentTheme.accent
            }

            MTK_HSeparator{}

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
                text: "Настройки калибровки"
                anchors.left: parent.left
                anchors.leftMargin: Style.panelsMargins*2
                horizontalAlignment: Text.AlignLeft
                height: Style.cardHeight
                color: Style.currentTheme.accent
            }

            MTK_HSeparator{}

            SliderCard{
                labelText: "Количество итерраций"
                from: 10
                to: 200
                value: appConfig.iterations
                stepSize: 1
                onMove: appConfig.iterations=value
            }

            SliderCard{
                labelText: "Точность приближения"
                from: 1
                to: 50
                value: appConfig.epsilon*divider
                stepSize: 1
                onMove: appConfig.epsilon=value/divider
                divider: appConfig.epsilonDivider
            }

            MTK_HSeparator{}

        }
    }
}
