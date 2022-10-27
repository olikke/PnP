import QtQuick 2.0

import "qrc:/QML/ElementBase"
import "qrc:/QML"

Item {
    id: root
    width: parent.width
    height: Style.cardHeight

    property bool editable: false

    property alias labelText: label.text
    property alias from: slider.from
    property alias to: slider.to
    property alias stepSize: slider.stepSize
    property alias value: slider.value
    property int divider: 1

    signal move(int value)

    MTK_RoundButton{
        id: btn
        anchors.left: parent.left
        anchors.leftMargin: Style.panelsMargins
        anchors.verticalCenter: parent.verticalCenter
        onClicked: parent.editable=!parent.editable
        width: Style.btnHeight
        height: Style.btnHeight
        text: (slider.value/divider).toString()
    }

    MTK_Label{
        id: label
        anchors.left: btn.right
        anchors.leftMargin: Style.panelsMargins*2
        anchors.verticalCenter: parent.verticalCenter
        visible: !parent.editable
        wrapMode: Text.Wrap
        anchors.right: parent.right
        anchors.rightMargin: Style.panelsMargins
        horizontalAlignment: Text.AlignLeft
    }

    MTK_Slider{
        id: slider
        anchors.left: btn.right
        anchors.leftMargin: Style.panelsMargins*2
        anchors.right: parent.right
        anchors.rightMargin: Style.panelsMargins
        anchors.verticalCenter: parent.verticalCenter
        visible: parent.editable
        onMoved: move(value)
    }
}
