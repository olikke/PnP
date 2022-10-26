import QtQuick 2.0
import QtQuick.Controls 2.4

import "qrc:/QML/ElementBase"
import "qrc:/QML"

Rectangle{
    color: Style.currentTheme.primary

    signal openFileDialog()
    signal startCalibrate()

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

            Item{
                width: parent.width
                height: Style.cardHeight

                MTK_RoundButton{
                    id: btn1
                    anchors.left: parent.left
                    anchors.leftMargin: Style.panelsMargins
                    anchors.verticalCenter: parent.verticalCenter
                    iconSource:"qrc:/ASSETS/icon/folder.svg"
                    onClicked: openFileDialog()
                    width: Style.btnHeight
                    height: Style.btnHeight
                    iconSize:Style.iconSize
                }

                MTK_Label{
                    anchors.left: btn1.right
                    anchors.leftMargin: Style.panelsMargins*2
                    wrapMode: Text.Wrap
                    anchors.right: parent.right
                    anchors.rightMargin: Style.panelsMargins
                    horizontalAlignment: Text.AlignLeft
                    anchors.verticalCenter: parent.verticalCenter
                    text: folderModel.folder!=""? folderModel.folder :"Выбрать изображения"
                }
            }

            MTK_HSeparator{}

            Item{
                width: parent.width
                height: Style.cardHeight

                MTK_RoundButton{
                    id: btn2
                    anchors.left: parent.left
                    anchors.leftMargin: Style.panelsMargins
                    anchors.verticalCenter: parent.verticalCenter
                    iconSource:"qrc:/ASSETS/icon/search.svg"
                    onClicked: startCalibrate()
                    width: Style.btnHeight
                    height: Style.btnHeight
                    iconSize:Style.iconSize
                }

                MTK_Label{
                    anchors.left: btn2.right
                    anchors.leftMargin: Style.panelsMargins*2
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Поиск и отображение углов"
                }
            }

            MTK_HSeparator{}
        }
    }
}
