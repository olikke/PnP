import QtQuick 2.0

Row{
    spacing: Style.connectionWidth

    Rectangle{
        width: parent.width-controlPanel.width-parent.spacing
        height: parent.height
        color: Style.currentTheme.primary

        Rectangle{
            id: rectangle
            property real ws: parent.width/frameWidth
            property real hs: parent.height/(frameHeight+buttons.height)
            property real mscale: ws<1 | hs<1 ?  ws<hs? ws: hs: 1
            width: frameWidth*mscale
            height: frameHeight*mscale+buttons.height
            anchors.centerIn: parent
            color: Style.currentTheme.background

            Connections{
                target: videoProvider
                onImageChanged: im.reload()
            }

            Image{
                id: im
                width: parent.width
                height: frameHeight*parent.mscale
                fillMode: Image.PreserveAspectFit
                antialiasing: true
                anchors.top: parent.top
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
                height: 48
                color: Style.currentTheme.primary
                Row{
                    height: 40
                    width: 120
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    spacing: Style.panelsMargins

                    MTK_RoundButton{
                        iconSource:"qrc:/ASSETS/icon/play.svg"
                        iconOnly: true
                        width: 40
                        height: width
                        enabled: cameraIndex.currentIndex!==-1
                        onClicked: grabber.startGrab(cameraIndex.currentIndex)
                    }

                    MTK_RoundButton{
                        iconSource:"qrc:/ASSETS/icon/photo.svg"
                        iconOnly: true
                        width: 40
                        height: width
                    }

                    MTK_RoundButton{
                        iconSource:"qrc:/ASSETS/icon/stop.svg"
                        iconOnly: true
                        width: 40
                        height: width
                        onClicked: grabber.stopGrab()
                    }
                }
            }
        }
    }

    Rectangle{
        id: controlPanel
        width: 300
        height: parent.height
        color: Style.currentTheme.background

        Column{
            anchors.fill: parent
            spacing: Style.connectionWidth

            Rectangle{
                width: parent.width
                height: Style.cardHeight
                color: Style.currentTheme.primary

                MTK_Label{
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.margins: Style.panelsMargins
                    text: "Открыть устройство захвата"
                    color: Style.currentTheme.accent
                }

                MTK_ComboBox{
                    id: cameraIndex
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    anchors.margins: Style.panelsMargins
                    customModel: camFinder.model
                    height: 24
                    currentIndex: -1
                }
            }

            Rectangle{
                width: parent.width
                height: Style.cardHeight
                color: Style.currentTheme.primary

                MTK_Label{
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.margins: Style.panelsMargins
                    text: "Папка"
                    color: Style.currentTheme.accent
                }

                Item{
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: 24
                    anchors.bottom: parent.bottom
                    anchors.margins: Style.panelsMargins

                    MTK_Label{
                        horizontalAlignment: Text.AlignLeft
                        text: "Текущая папка"
                        width: parent.width*0.6
                        anchors.left: parent.left
                    }

                    MTK_RoundButton{
                        anchors.right: parent.right
                        iconSource:"qrc:/ASSETS/icon/folder.svg"
                        iconOnly: true
                        width: 24
                        height: width
                    }

                }
            }



        }
    }
}

