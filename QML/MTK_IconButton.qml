import QtQuick 2.11
import QtGraphicalEffects 1.0

Item{
    id: root

    width: 24
    height: width

    property alias background: backgroundRectangle.color
    property alias color: overlay.color
    property alias source: icon.source
    property alias overlay: overlay
    property alias containsMouse: ma.containsMouse
    property alias iconScale: overlay.scale
    property real iconScaleValue: 1

    signal clicked()

    Rectangle{
        id: backgroundRectangle

        radius: height/2
        color: "transparent"
        scale: ma.pressed ? 0.8 : 1

        anchors.fill: parent

        Behavior on scale {
            NumberAnimation{
                duration: Style.animationDuration
            }
        }
    }

    Image{
        id:icon

        visible: false
        sourceSize.width: width
        sourceSize.height: height

        anchors.fill: parent
    }

    ColorOverlay{
        id: overlay

        source: icon
        color:  Style.currentTheme.foreground
        scale: ma.pressed ? iconScaleValue * 0.8 : iconScaleValue

        anchors.fill: icon

        Behavior on scale {
            NumberAnimation{
                duration: Style.animationDuration
            }
        }
    }

    MouseArea {
        id: ma

        hoverEnabled: true

        anchors.fill: parent

        onClicked: {
            root.clicked()
        }
    }
}
