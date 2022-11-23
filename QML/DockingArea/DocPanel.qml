import QtQuick 2.0
import QtQuick.Dialogs 1.3

import "qrc:/QML"

Row {
    id: root
    spacing: Style.connectionWidth

    Rectangle{
        width: parent.width-control.width-parent.spacing
        height: parent.height
        color: Style.currentTheme.primary

        Connections{
            target: dockProvider
            onImageChanged: im.reload()
        }

        Image{
            id: im
            fillMode: Image.PreserveAspectFit
            antialiasing: true
            source: "image://dlive/image"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            function reload() {
                source=""
                source="image://dlive/image"
            }
        }
    }

    DocControl{
        id: control
        width: Style.sidePanel
        height: parent.height
        onOpenImageDialog: openImage.open()
    }

    FileDialog {
        id: openImage
        title: "Открыть изображение"
        nameFilters: [ "Image files (*.bmp *.jpg *.png *.jpeg)"  ]
        onAccepted: {
           docking.openImage(fileUrl)
        }
    }
}
