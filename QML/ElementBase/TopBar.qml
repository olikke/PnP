import QtQuick 2.0
import QtGraphicalEffects 1.0

import "qrc:/QML"

Rectangle {
    height: 30
    color: Style.currentTheme.primary

    signal closeApp()
    signal minimizeApp()
    signal openTools(bool value)

    MTK_IconButton{
        property bool open: false
        anchors.right: minimize.left
        anchors.rightMargin: Style.panelsMargins
        source: "qrc:/ASSETS/icon/menu.svg"
        onClicked: {
            open=!open
            openTools(open)
            rotation=open? 90: 0
        }
        Behavior on rotation{ NumberAnimation {duration: Style.animationDuration*2}}
    }

    MTK_IconButton{
        id: minimize
        anchors.right: close.left
        anchors.rightMargin: Style.panelsMargins
        source: "qrc:/ASSETS/icon/minimize.svg"
        onClicked: minimizeApp()
    }

    MTK_IconButton{
        id: close
        anchors.right: parent.right
        anchors.rightMargin: Style.panelsMargins
        source: "qrc:/ASSETS/icon/close.svg"
        onClicked: closeApp()
    }



}
