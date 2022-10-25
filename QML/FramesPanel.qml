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


    Flickable{
        id: flick
        flickableDirection: Flickable.VerticalFlick
        contentHeight: repeater.height

        Repeater{
            id: repeater
            model:FolderListModel {
                id: folderModel
                objectName: "folderModel"
                showDirs: false
                nameFilters: ["*.jpeg",".jpg","*.bmp","*.png"]
            }
            Rectangle{
                id: photoFrame
                property int col: 5
                property int space: Style.connectionWidth*2
                width: (root.width-col*space)/col
                height: width*1200/1920+rec.height
                Component.onCompleted: console.log(index,folderModel.folder +fileName)
                x: index%col*(width+space)
                y: Math.floor(index/col)*(height+space)
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
