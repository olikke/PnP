import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import QtGraphicalEffects 1.0
import Qt.labs.folderlistmodel 1.0

import "."
import "qrc:/QML"
import "qrc:/QML/ElementBase"
import "qrc:/QML/Calibration"
import "qrc:/QML/Camera"
import "qrc:/QML/PnP"

ApplicationWindow {
    id: window
    visible: true
    color: Style.currentTheme.background
    width: Screen.width
    height: Screen.height
    flags: Qt.FramelessWindowHint

    Component.onCompleted: {
        Style.setDarkMode(true)
    }

    TopBar{
        id:topBar
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        onCloseApp: close()
        onMinimizeApp: window.showMinimized()

        Tabbar{
            id: tapbar
            height: parent.height/1.4
            backgroundVisible: false

            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: (parent.height - height)/2
            anchors.left: parent.left

            Tabbutton {
                text: "Захват с камеры"
            }

            Tabbutton {
                text: "Калибровка"
            }

            Tabbutton {
                text: "Устранение искажений"
            }

            Tabbutton {
                text: "Позиционирование"
            }
        }
    }


    SwipeView{
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.top: topBar.bottom
        anchors.topMargin: Style.connectionWidth
        clip: true
        currentIndex: tapbar.currentIndex
        interactive: false

        CameraPanel{
            id: cameraPanel
        }

        CalibrationPanel{
            id: framesPanel
        }

        PnPPanel{
            id: pnpPanel
        }
    }
}
