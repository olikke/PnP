import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.3

import "qrc:/QML"

Item {
    id: core
    property var customModel: ["1","2", "3"]
    property int indexUser : -1 //manual change index (by User)
    property alias currentIndex: list.currentIndex
    opacity: enabled ? 1 : 0.8
    Behavior on opacity { NumberAnimation { duration: Style.animationDuration; } }

    width: 60
    height: 18

    Rectangle{
        id:btn
        width: parent.width
        height: parent.height
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        color: enabled? Style.currentTheme.accent : Style.currentTheme.background
        radius:  height/2
        onEnabledChanged: canvas.requestPaint()

        Canvas{
            id:canvas
            x: parent.width - width - 10
            y: (parent.height - height) / 2
            width: 8
            height: 4
            contextType: "2d"
            onPaint: {
                context.reset()
                context.moveTo(0, 0)
                context.lineTo(width, 0)
                context.lineTo(width / 2, height)
                context.closePath()
                context.fillStyle = parent.enabled ? Style.currentTheme.foreground : Qt.lighter(Style.currentTheme.primary,1.4)
                context.fill()
            }
        }

        MTK_Label{
            id:textLabel

            anchors.fill: parent
            text:  (customModel &&  customModel.length!==0 && list.currentIndex!==-1) ? customModel[list.currentIndex]: " "
            leftPadding: 10
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            font.pointSize: 8
            wrapMode: Text.NoWrap
            clip: true
        }

        MouseArea {
            anchors.fill: parent
            onClicked: menu.popup(btn.x, btn.y)
        }

        Menu {
            id: menu
            background: Rectangle {
                implicitWidth: btn.width
                implicitHeight: 2
                radius: Style.unitRadius
                color: Qt.darker(Style.currentTheme.primary, 1.05)
                border.width: Style.connectionWidth
                border.color: Style.currentTheme.accent

            }

            contentItem: ListView {
                id: list
                model: customModel
                implicitHeight: contentHeight
                currentIndex: 0
                clip: true
                interactive: false
                delegate:
                    MTK_Label{
                    id: itemm
                    text: modelData
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    width: parent.width-anchors.leftMargin*2
                    horizontalAlignment: Text.AlignLeft
                    height: lineCount>1? Style.fieldHeight*lineCount/2: Style.fieldHeight
                    font.pointSize: 8

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            list.currentIndex=index
                            if (indexUser==index) indexUser=-1
                            indexUser = index
                            menu.close()
                        }
                    }

                    Rectangle {
                        opacity: index!==list.count-1? 1: 0
                        height: Style.connectionWidth
                        color: Style.currentTheme.accent
                        width: menu.width
                        anchors.bottom: itemm.bottom
                        anchors.bottomMargin: 1
                        anchors.left: itemm.left
                        anchors.leftMargin: -itemm.anchors.leftMargin
                    }
                }
            }
        }
    }
}

