import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import QtQuick.Dialogs 1.0
import QtGraphicalEffects 1.0
import Qt.labs.folderlistmodel 1.0

import "."
import "qrc:/QML"

ApplicationWindow {
    id: window
    visible: true
    color: Style.currentTheme.background
    width: Screen.width
    height: Screen.height
    flags: Qt.FramelessWindowHint

    property string _lastfolder: openDialog.shortcuts.home

    Component.onCompleted: {
        Style.setDarkMode(true)
    }

    Rectangle{
        id:topBar
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        height: 30
        color: Style.currentTheme.primary

        Image{
            id: icon
            visible: false
            anchors.left: parent.left
            anchors.leftMargin: Style.panelsMargins
            width: 20
            height: 20
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/ASSETS/icon/chess-horse-svgrepo-com.svg"

        }

        ColorOverlay{
            id: overlay
            source: icon
            color:  Style.currentTheme.accent
            anchors.fill: icon
        }

        MTK_Label{
            id: caption
            anchors.left: icon.right
            anchors.leftMargin: Style.panelsMargins
            anchors.verticalCenter: parent.verticalCenter
            text: "PnP"
        }

        MTK_IconButton{
            anchors.right: parent.right
            anchors.rightMargin: Style.panelsMargins
            source: "qrc:/ASSETS/icon/delete.svg"
            onClicked: close()
        }

        MouseArea {
            property int previousX
            property int previousY
            id: moveApp
            z: -1
            anchors.fill: parent
            onPressed: {
                previousX=mouseX
                previousY=mouseY
            }
            onMouseXChanged: {
                var dx = mouseX - previousX
                window.setX(window.x + dx)
                appConfig.x=window.x
            }
            onMouseYChanged: {
                var dy = mouseY - previousY
                window.setY(window.y + dy)
                appConfig.y=window.y
            }
        }
    }

    FileDialog {
        id: openDialog
        property bool left
        title: "Открыть папку с файлами"
        folder: _lastfolder
        selectFolder: true
      //  nameFilters: [ "Image files (*.bmp *.jpg *.png *.jpeg)"  ]
        onAccepted: {
            folderModel.folder=fileUrl+"/"
            _lastfolder=fileUrl
        }
    }

    Flickable{
        id: flickable
        width: 400
        anchors.right: parent.right
        anchors.top: topBar.bottom
        anchors.topMargin: Style.connectionWidth
        anchors.bottom: parent.bottom
        flickableDirection: Flickable.VerticalFlick
        contentHeight: control.height

        Column {
            id: control
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            spacing: Style.connectionWidth

            Rectangle{
                width: parent.width
                radius: Style.unitRadius
                height: sourceColumn.height+Style.panelsMargins*2
                color: Style.currentTheme.primary

                Column{
                    id: sourceColumn
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top
                    height: implicitHeight
                    anchors.margins: Style.panelsMargins
                    spacing: Style.panelsMargins

                    MTK_Label{
                        text: "Калибровка"
                        color: Style.currentTheme.accent
                    }

                    property int sourceIndex: 0

                    MTK_SwitchButton_2{
                        id: sourceButton
                        width: parent.width
                        text1: "Из папки"
                        text2: "С камеры"
                        index: 0
                    }

                    SwipeView{
                        width: parent.width
                        clip: true
                        height: 24
                        currentIndex: sourceButton.index

                        MTK_RoundButton{
                            text: "Открыть папку"
                            onClicked: openDialog.open()
                        }

                        Row{
                            spacing: 2

                            MTK_ComboBox{
                                width: parent.width-iconB.width*3-parent.spacing*3
                                height: parent.height
                            }

                            MTK_IconButton{
                                id: iconB
                                source: "qrc:/ASSETS/icon/play_circle_FILL0_wght400_GRAD0_opsz48.svg"
                            }

                            MTK_IconButton{
                                source: "qrc:/ASSETS/icon/pause_circle_FILL0_wght400_GRAD0_opsz48.svg"
                            }

                            MTK_IconButton{
                                source: "qrc:/ASSETS/icon/add_circle_FILL0_wght400_GRAD0_opsz48.svg"
                            }


                        }
                    }

//                    Item{
//                        id: fromFolder
//                        visible:true
//                        width: parent.width
//                        height: 50

//                        MTK_RoundButton{
//                            width: parent.width
//                            text: "Открыть папку"
//                        }
//                    }

//                    Item{
//                        id: fromKU
//                        visible:false
//                        width: parent.width
//                        height: 100
//                    }

                    Behavior on height {NumberAnimation {duration: Style.animationDuration}}
                }
            }


//            Rectangle{
//                width: parent.width
//                radius: Style.unitRadius
//                height: 75
//                color: Style.currentTheme.primary

//                Column{
//                    id: column
//                    anchors.fill: parent
//                    anchors.margins: Style.panelsMargins
//                    spacing: Style.panelsMargins

//                    MTK_Label{
//                        text: "Калибровка"
//                        color: Style.currentTheme.accent
//                    }

//                    MTK_HSeparator{
//                        opacity:0
//                        height: 5
//                    }

//                    Row{
//                        width: parent.width
//                        height: implicitHeight
//                        spacing: 11

//                        MTK_IconButton{
//                            source: "qrc:/ASSETS/icon/folder_open-black-48dp.svg"
//                        }

//                        MTK_IconButton{
//                            source: "qrc:/ASSETS/icon/videocam_FILL0_wght400_GRAD0_opsz48.svg"
//                        }

//                        MTK_VSeparator{}

//                        MTK_IconButton{
//                            source: "qrc:/ASSETS/icon/calculate_FILL0_wght400_GRAD0_opsz48.svg"
//                        }

//                        MTK_IconButton{
//                            source: "qrc:/ASSETS/icon/add_box_FILL0_wght400_GRAD0_opsz48.svg"
//                        }

//                        MTK_FramedLabel{
//                            height: 24
//                            text: "15 "
//                            border.color: Qt.lighter(Style.currentTheme.background,1.3)
//                        }

//                        MTK_VSeparator{}

//                        MTK_IconButton{
//                            source: "qrc:/ASSETS/icon/arrow_circle_left_FILL0_wght400_GRAD0_opsz48.svg"
//                        }

//                        MTK_IconButton{
//                            source: "qrc:/ASSETS/icon/arrow_circle_right_FILL0_wght400_GRAD0_opsz48.svg"
//                        }

//                        MTK_IconButton{
//                            source: "qrc:/ASSETS/icon/visibility_FILL0_wght400_GRAD0_opsz48.svg"
//                        }

//                        MTK_IconButton{
//                            source: "qrc:/ASSETS/icon/delete_FILL0_wght400_GRAD0_opsz48.svg"
//                        }

//                        MTK_VSeparator{}

//                        MTK_IconButton{
//                            source: "qrc:/ASSETS/icon/play_circle_FILL0_wght400_GRAD0_opsz48.svg"
//                        }

//                    }

//                }

//            }

//            Rectangle{
//                width: parent.width+5
//                radius: Style.unitRadius
//                height: Style.cardHeight
//                color: Style.currentTheme.primary

//            }

        }


    }


    Rectangle{
        anchors.left: parent.left
        anchors.right: flickable.left
        anchors.top: topBar.bottom
        anchors.bottom: parent.bottom
        anchors.margins: Style.connectionWidth
        color: Style.currentTheme.primary

        Repeater{
            model: FolderListModel {
                id: folderModel
                objectName: "folderModel"
                showDirs: false
            }
            Rectangle{
                id: photoFrame
                width: 50
                height: 50
                Image {
                    id: image
                    anchors.centerIn: parent
                    fillMode: Image.PreserveAspectFit
                    source: folderModel.folder + fileName
                    antialiasing: true
                }

            }
        }

    }

}
