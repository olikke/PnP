import QtQuick 2.0
import QtQuick.Controls 2.4

Rectangle{
    color: Style.currentTheme.primary

    signal openFileDialog()

    Flickable {
        id: root
        anchors.fill: parent
        flickableDirection: Flickable.VerticalFlick
        contentHeight: control.height

        Column {
            id: control
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            spacing: Style.connectionWidth


                Column{
                    id: sourceColumn
                    anchors.left: parent.left
                    anchors.right: parent.right
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
                            onClicked: openFileDialog()
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
                }


                MTK_HSeparator{opacity: 1}
        }
    }
}
