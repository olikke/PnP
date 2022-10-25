import QtQuick 2.11
import QtQuick.Controls 2.4

TabButton {
    id: control
    height: parent !== null ? parent.height : 0
    width: textWidth.width
    anchors.verticalCenter: parent !== null ? parent.verticalCenter : undefined

    contentItem: MTK_Label {
        id:txt
        opacity: enabled? 1: 0.3
        text: control.text
        anchors.fill: parent
        color: control.checked ? Style.foregroundDark : Style.currentTheme.foreground
        padding: 10
        font.pointSize: 12

        MTK_Label{
            id: textWidth
            text: parent.text
            font.pointSize: 12
            padding: 10
            visible: false
        }
    }
    background: Rectangle {
        anchors.fill: parent
        radius: Style.rounded ? height/2 : Style.unitRadius
        color: "transparent"
    }
}
