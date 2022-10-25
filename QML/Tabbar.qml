import QtQuick 2.9
import QtQuick.Templates 2.2 as T

import "."

T.TabBar {
    id: control
    implicitWidth: contentWidth
    height: parent.height
    spacing: 2

    property alias backgroundVisible: background.visible

    contentItem: ListView {
        highlightResizeDuration: Style.animationDuration
        highlightMoveDuration: Style.animationDuration
        model: control.contentModel
        currentIndex: control.currentIndex
        spacing: control.spacing
        orientation: ListView.Horizontal
        boundsBehavior: Flickable.StopAtBounds
        flickableDirection: Flickable.AutoFlickIfNeeded
        snapMode: ListView.SnapToItem

        highlightRangeMode: ListView.ApplyRange

        highlight: Item {
            Rectangle {
                height: control.height
                width: parent.width
                radius: Style.rounded ? height/2 : Style.unitRadius
                color: Style.currentTheme.accent
            }
        }
    }

    background: Rectangle {
        id: background
        width: control.width
        height: control.height
        radius: Style.rounded ? height/2 : Style.unitRadius
        anchors.fill: parent
        color: Style.isDarkMode ? Style.currentTheme.background : Style.currentTheme.lightBackground
    }
}
