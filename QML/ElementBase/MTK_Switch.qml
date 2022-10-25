import QtQuick 2.11
import QtQuick.Controls 2.2

import "qrc:/QML"

Switch {
    id: control
    implicitWidth: 42
    implicitHeight: 22
    property bool alwaysAccent: false
    property real disableOpacity: Style.disableControlsOpacity
    opacity: enabled ? 1 : 0.8
    Behavior on opacity { NumberAnimation { duration: Style.animationDuration; } }

    indicator: Rectangle {
        id: rectangle
        x: border.width
        implicitWidth: parent.width
        implicitHeight: parent.height
        radius: height/2
        anchors.verticalCenter: parent.verticalCenter
        color: alwaysAccent? Style.currentTheme.accent: control.checked ? Style.currentTheme.accent : Style.isDarkMode ? Style.currentTheme.background : Style.currentTheme.lightBackground

        Behavior on color{  ColorAnimation{ duration: Style.animationDuration*2; easing.type: Easing.InOutQuad }}

        Rectangle {
            x: control.checked ? parent.width - width - Style.connectionWidth : Style.connectionWidth
            width: control.height - (Style.connectionWidth * 2)
            height: width
            radius: width/2
            anchors.verticalCenter: parent.verticalCenter
            color:Style.currentTheme.primary

            Behavior on x{  NumberAnimation{ duration: Style.animationDuration; easing.type: Easing.InOutQuad }}
            Behavior on color{ ColorAnimation{ duration: Style.animationDuration; easing.type: Easing.InOutQuad }}
        }
    }
}
