import QtQuick 2.9
import QtQuick.Controls 2.4
import QtQuick.Controls.impl 2.4
import QtQuick.Templates 2.4 as T

import "qrc:/QML"

Drawer {
    id: control

    dim:true
    dragMargin: -1
    parent: T.Overlay.overlay
    //interactive: false

    property bool isOpen: control.position > 0

    implicitWidth: Math.max(background ? background.implicitWidth : 0, contentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(background ? background.implicitHeight : 0, contentHeight + topPadding + bottomPadding)

    contentWidth: contentItem.implicitWidth || (contentChildren.length === 1 ? contentChildren[0].implicitWidth : 0)
    contentHeight: contentItem.implicitHeight || (contentChildren.length === 1 ? contentChildren[0].implicitHeight : 0)

    topPadding: control.edge === Qt.BottomEdge
    leftPadding: control.edge === Qt.RightEdge
    rightPadding: control.edge === Qt.LeftEdge
    bottomPadding: control.edge === Qt.TopEdge

    closePolicy: Popup.CloseOnPressOutside

    enter: Transition {  NumberAnimation { property: "position"; from: 0; to: 1; duration: 200; /*easing.type: Easing.InOutQuint*/ } }
    exit: Transition {  NumberAnimation { property: "position"; from: 1; to: 0; duration: 200; /*easing.type: Easing.InOutQuint*/ } }

//    Behavior on position {
//        NumberAnimation{
//            duration: 200
//            easing.type: Easing.InQuart
//        }
//    }

    background: Item {
        Item {
            readonly property bool horizontal: control.edge === Qt.LeftEdge || control.edge === Qt.RightEdge
            width: horizontal ? 1 : parent.width
            height: horizontal ? parent.height : 1
            x: control.edge === Qt.LeftEdge ? parent.width - 1 : 0
            y: control.edge === Qt.TopEdge ? parent.height - 1 : 0
        }
    }

    T.Overlay.modal: Rectangle {
        color: Color.transparent(Style.currentTheme.fadeColor, Style.fadeOpacity)
        Behavior on color{ ColorAnimation{ duration: Style.animationDuration; /*easing.type: Easing.InOutQuad*/ }}
    }

//    T.Overlay.modeless: Rectangle {
//        color: Color.transparent(Style.foregroundDark, Style.fadeOpacity)
//        Behavior on color{ ColorAnimation{ duration: Style.animationDuration; /*easing.type: Easing.InOutQuad*/ }}
//    }
}
