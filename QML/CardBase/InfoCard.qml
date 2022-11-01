import QtQuick 2.0

import "qrc:/QML/ElementBase"
import "qrc:/QML"

Item {
    id: root
    width: parent.width
    height: Style.cardHeight*0.8

    property alias infoText: label1.text
    property alias labelText: label2.text

    MTK_FramedLabel{
        id: label1
        anchors.left: parent.left
        anchors.leftMargin: Style.panelsMargins
        anchors.verticalCenter: parent.verticalCenter
        width: Style.btnHeight
        height: Style.btnHeight*0.8
        radius: Style.unitRadius/2
        border.color: Style.currentTheme.background
    }

    MTK_Label{
        id: label2
        anchors.left: label1.right
        anchors.leftMargin: Style.panelsMargins*2
        anchors.verticalCenter: parent.verticalCenter
        wrapMode: Text.Wrap
        anchors.right: parent.right
        anchors.rightMargin: Style.panelsMargins
        horizontalAlignment: Text.AlignLeft
    }

}
