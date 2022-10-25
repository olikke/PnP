import QtQuick 2.9
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.3

import "qrc:/QML"

Rectangle {
    id: root

    width: textt.width + 20
    height: textt.height + 10
    color: "transparent"
    border.color: Style.currentTheme.foreground
    radius: Style.rounded ? height/2 : Style.unitRadius
    border.width: Style.connectionWidth

    property alias text: textt.text
    property alias fontSize: textt.font.pixelSize
    property int textWidth: 0//metrics.width + 20
    property color fontColor: Style.currentTheme.foreground

    Text{
        id: textt

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.family: Style.robotoCondensed
        font.bold: true
        font.pixelSize: 14
        color: fontColor
        wrapMode: Text.NoWrap

        anchors.centerIn: parent
    }
}
