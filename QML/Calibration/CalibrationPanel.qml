import QtQuick 2.9
import Qt.labs.folderlistmodel 1.0
import QtQuick.Dialogs 1.3

import "qrc:/QML/ElementBase"
import "qrc:/QML"

Item{
    Row {
        id: root
        anchors.fill: parent
        spacing: Style.connectionWidth

        FileDialog {
            id: openDialog
            title: "Открыть папку с файлами"
            folder: folderBack.url
            selectFolder: true
            onAccepted: {
                onAccepted: folderModel.folder = fileUrl + "/"
            }
        }

        Flickable{
            id: flick
            width: parent.width-calibrationControl.width-parent.spacing
            height: parent.height
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
                    id: repeater
                    model:    FolderListModel {
                        id: folderModel
                        folder: ""
                        objectName: "folderModel"
                        showDirs: false
                        nameFilters: ["*.jpeg",".jpg","*.bmp","*.png"]
                    }

                    Rectangle{
                        id: photoFrame
                        width: (parent.width-grid.columns*grid.spacing)/grid.columns
                        height: width*appConfig.frameHeight/appConfig.frameWidth+rec.height
                        color: "transparent"

                        property string fn: fileName
                        property bool ch: true

                        Image {
                            id: image
                            anchors.fill: parent
                            anchors.bottomMargin: rec.height
                            anchors.horizontalCenter: parent.horizontalCenter
                            fillMode: Image.PreserveAspectFit
                            source: folderModel.folder + fileName
                            antialiasing: true
                            MouseArea{
                                anchors.fill: parent
                                onDoubleClicked: fullscreenItem.start(image.source,photoFrame.x,-flick.visibleArea.yPosition*flick.contentHeight+photoFrame.y,image.width,image.height)
                            }
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
                                property int awidth: parent.width-cb.width-l2.width-spacing*2
                                MTK_Checkbox{
                                    id: cb
                                    height: 24
                                    width: 30
                                    uncheckedColor: Style.currentTheme.foreground
                                    checked: true
                                    onCheckStateChanged: ch=checked
                                }
                                MTK_Label{
                                    id: l1
                                    text: fileName
                                    anchors.verticalCenter: parent.verticalCenter
                                    width: contentWidth>parent.awidth? parent.awidth: contentWidth
                                    clip: true
                                }
                                MTK_Label{
                                    id: l2
                                    text: image.sourceSize.width+"x"+image.sourceSize.height
                                    anchors.verticalCenter: parent.verticalCenter
                                }
                            }
                        }
                    }
                }
            }
        }

        CalibrationControl{
            id: calibrationControl
            width: Style.sidePanel
            height: parent.height
            onOpenFileDialog: openDialog.open()
            onStartCalibrate: {
                var recomendationList=[]
                var number=0
                for (var i=0; i< repeater.count; i++) {
                    var element=repeater.itemAt(i);
                    if (element.ch) recomendationList[number++]=element.fn
                }
                calibrate.start(folderModel.folder,recomendationList)
            }
        }
    }

    Rectangle{
        id: fullscreenItem
        property int xx:0
        property int yy:0
        property int ww:0
        property int hh:0
        x:xx;y:yy;width:ww; height:hh
        function start(_image, _x, _y, _width, _height) {
            xx=_x
            yy=_y
            ww=_width
            hh=_height
            fullImage.source=_image
            fullscreenItem.state="fill"
        }
        function end() {
            fullscreenItem.state="*"
            xx=0;
            yy=0;
            ww=0;
            hh=0;
        }

        Image{
            id: fullImage
            anchors.fill: parent
        }

        states: [
            State{
                name: "*"
                PropertyChanges {target: fullscreenItem;  x:xx;y:yy;width:ww; height:hh}
            },

            State {
                name: "fill"
                PropertyChanges {target: fullscreenItem;  x:0; y:0;width: root.width;height:root.height}
            }
        ]

        transitions: [
            Transition {
                from: "*"; to: "fill"
                NumberAnimation{properties: "x,y,width,height"; duration: Style.animationDuration*2; easing.type: Easing.InQuart}
            },
            Transition {
                from: "fill"; to: "*"
                NumberAnimation{properties: "x,y,width,height"; duration: Style.animationDuration*2; easing.type: Easing.InQuart}
            }
        ]

        MouseArea{
            anchors.fill: parent
            onDoubleClicked: fullscreenItem.end()
        }
    }
}
