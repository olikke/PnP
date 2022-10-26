import QtQuick 2.0
import QtGraphicalEffects 1.0

import "qrc:/QML"

Rectangle {
    height: 30
    color: Style.currentTheme.primary

    signal closeApp()
    signal minimizeApp()

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
