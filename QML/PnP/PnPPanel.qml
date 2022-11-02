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
            target: pnpProvider
            onImageChanged: im.reload()
        }

        Image{
            id: im
            fillMode: Image.PreserveAspectFit
            antialiasing: true
            source: "image://plive/image"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            function reload() {
                source=""
                source="image://plive/image"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: pnpos.findPoint(Qt.point(mouseX,mouseY))
            }
        }

    }

    PnPControl{
        id: control
        width: Style.sidePanel
        height: parent.height

        onOpenImageDialog: openImage.open()
        onOpenMatrixDialog: openXML.open()
    }

    FileDialog {
        id: openImage
        title: "Открыть изображение"
        nameFilters: [ "Image files (*.bmp *.jpg *.png *.jpeg)"  ]
        onAccepted: {
           pnpos.openImage(fileUrl)
        }
    }

    FileDialog {
        id: openXML
        title: "Открыть результаты калибровки камеры"
        nameFilters: [ "XML files (*.xml)"  ]
        onAccepted: {
            pnpos.openMatrix(fileUrl)
        }
    }


}

