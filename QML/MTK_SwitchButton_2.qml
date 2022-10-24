import QtQuick 2.0


Item {
    id:root

    implicitHeight: 22
    implicitWidth: 200
    width: 200
    height: 22
    property int fontValue: 10
    property real disableOpacity: Style.disableControlsOpacity
    property alias text1: text1.text
    property alias text2: text2.text
    property int index: 0
    opacity: enabled ? 1 : 0.8

    Behavior on opacity {
        NumberAnimation {
            duration: Style.animationDuration
        }
    }

    Rectangle {
        id: rectangle

        radius: Style.rounded ? height/2 : Style.unitRadius
        color: Style.isDarkMode ? Style.currentTheme.background : Style.currentTheme.lightBackground

        anchors.fill: parent
    }

    Rectangle {
        id:accentRectangle
        x: root.index > 0 ? parent.width/2 : 0
        width: parent.width/2
        height: parent.height
        color: Style.currentTheme.accent
        radius: Style.rounded ? height/2 : Style.unitRadius
        anchors.verticalCenter: parent.verticalCenter

        Behavior on x{
            NumberAnimation {
                duration: Style.animationDuration
            }
        }
    }

    Item {
        clip: true

        anchors.right: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.top: parent.top

        MTK_Label{
            id: text1

            text: "text 1"
            font.pointSize: fontValue
            anchors.fill: parent
            color:index == 0 ? Style.foregroundDark: Style.currentTheme.foreground

            Behavior on x{
                NumberAnimation {
                    duration: Style.animationDuration
                }
            }
        }

        MouseArea { anchors.fill: parent; onClicked: index = 0; }
    }

    Item {
        clip: true

        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: parent.horizontalCenter

        MTK_Label{
            id: text2

            text: "text 2"
            font.pointSize: fontValue
            anchors.fill: parent
            color: index == 1 ? Style.foregroundDark: Style.currentTheme.foreground

            Behavior on x{
                NumberAnimation {
                    duration: Style.animationDuration
                }
            }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: index = 1
        }
    }

    Rectangle {
        id: disabledBackground

        radius: Style.rounded ? Math.min(width, height)/2 : Style.unitRadius
        color: Style.currentTheme.background
        opacity: !root.enabled ? disableOpacity : 0

        anchors.fill: parent

        Behavior on opacity {
            NumberAnimation {
                duration: Style.animationDuration
            }
        }
    }
}
