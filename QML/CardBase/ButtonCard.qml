import QtQuick 2.0

import "qrc:/QML/ElementBase"
import "qrc:/QML"

Item {
    id: root
    width: parent.width
    height: Style.cardHeight

    property alias iconSource: btn.iconSource
    property alias labelText: label.text

    signal clicked()

    MTK_RoundButton{
        id: btn
        anchors.left: parent.left
        anchors.leftMargin: Style.panelsMargins
        anchors.verticalCenter: parent.verticalCenter
        onClicked: root.clicked()
        width: Style.btnHeight
        height: Style.btnHeight
        iconSize:Style.iconSize
    }

    MTK_Label{
        id: label
        anchors.left: btn.right
        anchors.leftMargin: Style.panelsMargins*2
        anchors.verticalCenter: parent.verticalCenter
        wrapMode: Text.Wrap
        anchors.right: parent.right
        anchors.rightMargin: Style.panelsMargins
        horizontalAlignment: Text.AlignLeft
    }

}
