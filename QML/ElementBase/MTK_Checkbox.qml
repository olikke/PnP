import QtQuick 2.6
import QtQuick.Controls 2.1

import "qrc:/QML"

CheckBox {
    id: control

    enabled: true

    property color checkedColor: Style.currentTheme.accent
    property color uncheckedColor: Style.currentTheme.background

    indicator: Rectangle {
        implicitWidth: 20
        implicitHeight: 20
        x: control.leftPadding
        y: parent.height / 2 - height / 2
        radius: 4
        border.color: control.checked ? checkedColor : uncheckedColor
        color: "transparent"
        border.width: 2

        Rectangle {
            width: 10
            height: 10
            x: 5
            y: 5
            radius: 2
            color: checkedColor
            visible: control.checked
        }
    }

    contentItem: Text {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: Style.currentTheme.foreground
        verticalAlignment: Text.AlignVCenter
        leftPadding: control.indicator.width + control.spacing
    }
}
