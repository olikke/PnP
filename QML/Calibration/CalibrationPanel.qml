import QtQuick 2.9
import QtQuick.Window 2.2
import Qt.labs.folderlistmodel 1.0
import QtQuick.Dialogs 1.3

import "qrc:/QML/ElementBase"
import "qrc:/QML"

Row {
    id: root
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
                            onDoubleClicked: {
                                fullscreenItem.set(image.source,photoFrame.x+x,photoFrame.y+y,image.width,image.height)
//                                fullscreenItem.start()
                            }
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

    Rectangle{
        id: fullscreenItem
        function set(_image, _x, _y, _width, _height) {
            x=_x
            y=_y
            width=_width*2
            height=_height*2
            visible=true
        }


//        states: State{
//            name: "in"
//            PropertyChanges{target: fullscreenItem; x: 0; y: 0; width:Screen.width; height: Screen.height}
//        }
    width:0
    height: 0
      //  visible: false
        color: "green"

//        ParallelAnimation{
//            id: anim
//            NumberAnimation { property: "width"; to: root.width; duration: 1000}
//            NumberAnimation { property: "height"; to: root.height; duration: 1000}
//        }

        MouseArea{
            anchors.fill: parent
            onDoubleClicked: parent.visible=false
        }

    }

}
