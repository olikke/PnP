import QtQuick 2.11
import QtQuick.Controls 2.2

import "qrc:/QML"

Slider {
    id: control
    height: 6
    property alias progressLineColor: progressLine.color
    property alias grooveColor: groove.color
    property alias backgroundColor: background.color
    property bool forceRoundDisabled: false
    value: 0.5
    padding:0
    hoverEnabled: true

    opacity: enabled ? 1 : 0.8
    Behavior on opacity { NumberAnimation { duration: Style.animationDuration; } }

    background: Rectangle {
        id:background
        x: control.leftPadding
        y: control.topPadding + control.availableHeight / 2 - height / 2
        implicitWidth: 200
        implicitHeight: control.height
        width: control.availableWidth
        height: implicitHeight
        color: Style.isDarkMode ? Style.currentTheme.background : Style.currentTheme.lightBackground
        radius: Style.rounded ? (!forceRoundDisabled ? height/2 : 0) : Style.unitRadius

        Rectangle {
            id:progressLine
            width: control.visualPosition * parent.width
            height: parent.height
            color: control.enabled? Style.currentTheme.accent : Style.currentTheme.background
            radius: Style.rounded ? (!forceRoundDisabled ? height/2 : 0) : Style.unitRadius
        }
    }

    handle: Rectangle {
        id:groove
        x: progressLine.width - width/2
        y: control.topPadding + control.availableHeight / 2 - height / 2
        implicitWidth: control.height * 1.8
        implicitHeight: control.height * 1.8
        radius: height/2
        color: progressLine.color
        opacity:0

        Behavior on opacity { NumberAnimation { duration: Style.animationDuration } }
    }
    onPressedChanged: pressed?groove.opacity = 1: groove.opacity = 0
}
