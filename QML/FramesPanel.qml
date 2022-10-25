import QtQuick 2.9
import Qt.labs.folderlistmodel 1.0
import QtQuick.Dialogs 1.0

Rectangle {
    id: root
    color: Style.currentTheme.background

    function openFileDialog() {openDialog.open()}

    property string _lastfolder: openDialog.shortcuts.home

    FileDialog {
        id: openDialog
        property bool left
        title: "Открыть папку с файлами"
        folder: _lastfolder
        selectFolder: true
        onAccepted: {
            onAccepted: folderModel.folder = fileUrl + "/"
            _lastfolder=fileUrl
        }
    }

    ControlPanel{
        id: controlPanel
        width: 400
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        onOpenFileDialog: framesPanel.openFileDialog()
    }

    Flickable{
        id: flick
        anchors.fill: parent
        anchors.rightMargin: controlPanel.width
        flickableDirection: Flickable.VerticalFlick
        contentHeight: grid.height+60
        clip: true

        Grid{
            id: grid
            width: parent.width
            height: implicitHeight
            columns: 5
            spacing: 5

            Repeater{
                model:FolderListModel {
                    id: folderModel
                    objectName: "folderModel"
                    showDirs: false
                    nameFilters: ["*.jpeg",".jpg","*.bmp","*.png"]
                }
                Rectangle{
                    id: photoFrame
                    width: (parent.width-grid.columns*grid.spacing)/grid.columns
                    height: width*frameHeight/frameWidth+rec.height
                    color: "transparent"

                    Image {
                        id: image
                        anchors.fill: parent
                        anchors.bottomMargin: rec.height
                        anchors.horizontalCenter: parent.horizontalCenter
                        fillMode: Image.PreserveAspectFit
                        source: folderModel.folder + fileName
                        antialiasing: true
                    }
                    Rectangle{
                        id: rec
                        width: parent.width
                        height: 24
                        anchors.bottom: parent.bottom
                        color: "transparent"
                        Row{
                            width: parent.width
                            spacing: Style.panelsMargins
                            MTK_Checkbox{
                                height: 24
                                width: 30
                                uncheckedColor: Style.currentTheme.foreground
                                checked: true
                            }
                            MTK_Label{
                                text: fileName
                                anchors.verticalCenter: parent.verticalCenter
                            }
                            MTK_Label{
                                text: image.sourceSize.width+"x"+image.sourceSize.height
                                anchors.verticalCenter: parent.verticalCenter
                            }
                        }
                    }
                }
            }
        }
    }
}
