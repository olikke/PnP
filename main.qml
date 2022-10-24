import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import QtQuick.Dialogs 1.0
import QtGraphicalEffects 1.0
import Qt.labs.folderlistmodel 1.0

import "."
import "qrc:/QML"

ApplicationWindow {
    id: window
    visible: true
    color: Style.currentTheme.background
    width: Screen.width
    height: Screen.height
    flags: Qt.FramelessWindowHint

    property string _lastfolder: openDialog.shortcuts.home

    Component.onCompleted: {
        Style.setDarkMode(true)
    }

    TopBar{
        id:topBar
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        onCloseApp: close()
    }



    FileDialog {
        id: openDialog
        property bool left
        title: "Открыть папку с файлами"
        folder: _lastfolder
        selectFolder: true
        onAccepted: {
            frameModel.reload(fileUrl+"/")
            _lastfolder=fileUrl
        }
    }

    ControlPanel{
        id: controlPanel
        width: 400
        anchors.right: parent.right
        anchors.top: topBar.bottom
        anchors.topMargin: Style.connectionWidth
        anchors.bottom: parent.bottom
    }

    FramesPanel{
        id: framesPanel
        anchors.left: parent.left
        anchors.right: controlPanel.left
        anchors.top: topBar.bottom
        anchors.bottom: parent.bottom
        anchors.margins: Style.connectionWidth
    }

}
