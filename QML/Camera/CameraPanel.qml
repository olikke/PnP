import QtQuick 2.0

import "qrc:/QML/ElementBase"
import "qrc:/QML"

Row{
    spacing: Style.connectionWidth

    Rectangle{
        width: parent.width-cameraControl.width-parent.spacing
        height: parent.height
        color: Style.currentTheme.primary

        Rectangle{
            id: rectangle
            property real ws: parent.width/frameWidth
            property real hs: parent.height/(frameHeight+buttons.height+combo.height)
            property real mscale: ws<1 | hs<1 ?  ws<hs? ws: hs: 1
            width: frameWidth*mscale
            height: frameHeight*mscale+buttons.height+combo.height
            anchors.centerIn: parent
            color: Style.currentTheme.background

            Connections{
                target: videoProvider
                onImageChanged: im.reload()
            }

            Rectangle{
                id: combo
                width: parent.width
                anchors.top:parent.top
                height: 56
                color: Style.currentTheme.primary

                MTK_ComboBox{
                    id: cb
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 10
                    anchors.horizontalCenter: parent.horizontalCenter
                    customModel: camFinder.model
                    height: 24
                    width:150
                    currentIndex: -1
                }
            }

            Image{
                id: im
                height: frameHeight*parent.mscale
                fillMode: Image.PreserveAspectFit
                antialiasing: true
                anchors.top: combo.bottom
                anchors.bottom: buttons.top
                source: "image://mlive/image"
                function reload() {
                    source= ""
                    source = "image://mlive/image"
                }
            }
            Rectangle{
                id: buttons
                width: parent.width
                anchors.bottom: parent.bottom
                height: Style.cardHeight
                color: Style.currentTheme.primary
                Row{
                    height: Style.btnHeight
                    width: 120
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: Style.panelsMargins

                    MTK_RoundButton{
                        iconSource:"qrc:/ASSETS/icon/play.svg"
                        iconOnly: true
                        width: 40
                        height: width
                        enabled: cb.cameraIndex!==-1
                        onClicked: grabber.startGrab(cb.currentIndex)
                    }

                    MTK_RoundButton{
                        iconSource:"qrc:/ASSETS/icon/photo.svg"
                        iconOnly: true
                        width: 40
                        height: width
                        enabled: grabber.play & grabber.folderReady
                        onClicked: grabber.makePhoto()
                    }

                    MTK_RoundButton{
                        iconSource:"qrc:/ASSETS/icon/stop.svg"
                        iconOnly: true
                        width: 40
                        height: width
                        onClicked: grabber.stopGrab()
                        enabled: grabber.play
                    }
                }
            }
        }
    }

    CameraControl{
        id: cameraControl
        width: Style.sidePanel
        height: parent.height
    }
}

