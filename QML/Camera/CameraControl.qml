import QtQuick 2.0
import Qt.labs.folderlistmodel 1.0
import QtQuick.Dialogs 1.3

import "qrc:/QML/ElementBase"
import "qrc:/QML/CardBase"
import "qrc:/QML"

Rectangle{
    id: root
    color: Style.currentTheme.primary

    FileDialog {
        id: openDialog
        title: "Создайте папку"
        folder: folderBack.url
        selectFolder: true
        onAccepted: {
            folderBack.url=fileUrl+"/"
            folderModel.folder= folderBack.url
            lbl1.labelText=folderBack.url
            grabber.setUrl(folderModel.folder)
        }
    }

    Column{
        id: col
        width: parent.width
        height: implicitHeight
        spacing: Style.connectionWidth

        ButtonCard{
            id: lbl1
            iconSource:"qrc:/ASSETS/icon/folder.svg"
            labelText: "Выбрать папку для сохранения"
            onClicked: openDialog.open()
        }

        MTK_HSeparator{}
    }

    Flickable{
        id: flick
        width: parent.width
        anchors.top: col.bottom
        anchors.bottom: parent.bottom
        flickableDirection: Flickable.VerticalFlick
        contentHeight: grid.height
        clip: true

        Grid{
            id: grid
            width: parent.width
            height: implicitHeight
            columns: 2
            spacing: Style.connectionWidth*2

            Repeater{
                model:     FolderListModel {
                    id: folderModel
                    folder: ""
                    objectName: "folderModel"
                    showDirs: false
                    nameFilters: ["*.jpeg",".jpg","*.bmp","*.png"]
                }

                Rectangle{
                    id: photoFrame
                    width: grid.width/grid.columns-grid.spacing*(grid.columns-1)
                    height: width*appConfig.frameHeight/appConfig.frameWidth
                    color: Style.currentTheme.primary

                    Image {
                        id: image
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectFit
                        source: folderModel.folder + fileName
                        antialiasing: true

                        MouseArea{
                            anchors.fill: parent
                            onClicked: console.log("hello")
                        }

                        MTK_RoundButton{
                            anchors.right: parent.right
                            anchors.bottom: parent.bottom
                            anchors.margins: Style.panelsMargins
                            iconSource:"qrc:/ASSETS/icon/delete.svg"
                            width: Style.btnHeight/2
                            height: Style.btnHeight/2
                            iconSize:Style.iconSize/2
                            onClicked: folderBack.deleteOne(fileName)
                        }
                    }
                }
            }
        }
    }
}
