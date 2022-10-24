import QtQuick 2.0
import QtGraphicalEffects 1.0

import "."

Rectangle {
    height: 30
    color: Style.currentTheme.primary

    signal closeApp()

    Image{
        id: icon
        visible: false
        anchors.left: parent.left
        anchors.leftMargin: Style.panelsMargins
        width: 20
        height: 20
        anchors.verticalCenter: parent.verticalCenter
        source: "qrc:/ASSETS/icon/chess-horse-svgrepo-com.svg"
    }

    ColorOverlay{
        id: overlay
        source: icon
        color:  Style.currentTheme.accent
        anchors.fill: icon
    }

    MTK_Label{
        id: caption
        anchors.left: icon.right
        anchors.leftMargin: Style.panelsMargins
        anchors.verticalCenter: parent.verticalCenter
        text: "PnP"
    }

    MTK_IconButton{
        anchors.right: parent.right
        anchors.rightMargin: Style.panelsMargins
        source: "qrc:/ASSETS/icon/delete.svg"
        onClicked: closeApp()
    }



}
