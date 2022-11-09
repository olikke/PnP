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
                console.log("newImage")
                source=""
                source="image://plive/image"
            }
            Target{
                id: trg
                number: pnp.pointNumb
                visible: true;
                width: 20
                opacity: 0.5
                x: ma.mouseX-width/2
                y:ma.mouseY-height/2
            }
            MouseArea{
                id: ma
                hoverEnabled: true
                anchors.fill: parent
                onClicked: pnp.findPoint(Qt.point(mouseX,mouseY))
                onEntered: trg.visible=true
                onExited: trg.visible=false
                onWheel: pnp.changePointNumb(wheel.angleDelta.y>0)
            }
            Repeater{
                model: 5
                Target{
                    number: index
                    Connections{
                        target: pnp
                        onPaintTarget:  if (numb==number) {
                                            visible=true
                                            x=point.x-width/2;
                                            y=point.y-width/2
                                        }
                        onClearTarget: if (numb==number) visible=false
                        onClearAll: visible=false;
                    }
                    visible: false
                    width: 20
                }
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
           pnp.openImage(fileUrl)
        }
    }

    FileDialog {
        id: openXML
        title: "Открыть результаты калибровки камеры"
        nameFilters: [ "XML files (*.xml)"  ]
        onAccepted: {
            pnp.openMatrix(fileUrl)
        }
    }


}

