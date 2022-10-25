import QtQuick 2.0
import QtGraphicalEffects 1.0

import "."

Rectangle {
    height: 30
    color: Style.currentTheme.primary

    signal closeApp()

    MTK_IconButton{
        anchors.right: parent.right
        anchors.rightMargin: Style.panelsMargins
        source: "qrc:/ASSETS/icon/close.svg"
        onClicked: closeApp()
    }



}
