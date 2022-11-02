import QtQuick 2.0

import "qrc:/QML/ElementBase"
import "qrc:/QML/CardBase"
import "qrc:/QML"

Rectangle{
    color: Style.currentTheme.primary

    signal openImageDialog()
    signal openMatrixDialog()

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

            ButtonCard{
                iconSource:"qrc:/ASSETS/icon/folder.svg"
                labelText:  "Выбрать изображение"
                onClicked: openImageDialog()
            }

            MTK_HSeparator{}

            ButtonCard{
                iconSource:"qrc:/ASSETS/icon/matrix.svg"
                labelText:  "Загрузить параметры камеры"
                onClicked: openMatrixDialog()
            }

            MTK_HSeparator{}

            MTK_Label{
                text: "Матрица внутренних параметров камеры"
                anchors.left: parent.left
                anchors.leftMargin: Style.panelsMargins*2
                horizontalAlignment: Text.AlignLeft
                height: Style.cardHeight
                color: Style.currentTheme.accent
            }

            MTK_HSeparator{}

            MatTableCard{
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: Style.panelsMargins
                model: pnpos.getCameraModel()
            }

            MTK_HSeparator{}

            MTK_Label{
                text: "Матрица коэффициентов искажений"
                anchors.left: parent.left
                anchors.leftMargin: Style.panelsMargins*2
                horizontalAlignment: Text.AlignLeft
                height: Style.cardHeight
                color: Style.currentTheme.accent
            }

            MTK_HSeparator{}

            MatTableCard{
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: Style.panelsMargins
                model: pnpos.getDistModel()
            }

            MTK_HSeparator{}

            MTK_Label{
                text: "Ввод точек изображения (окружность)"
                anchors.left: parent.left
                anchors.leftMargin: Style.panelsMargins*2
                horizontalAlignment: Text.AlignLeft
                color: Style.currentTheme.accent
                height: Style.cardHeight
            }

            MTK_HSeparator{}

           Rectangle{
               width: parent.width
               height: 10
               color: "transparent"
           }

           Image{
               anchors.left: parent.left
               anchors.right: parent.right
               anchors.margins: Style.panelsMargins
               height: width
               source: "qrc:/ASSETS/Checkerboard.png"

               Item{
                   width: 40
                   height: 40
                   anchors.verticalCenter: parent.verticalCenter
                   anchors.horizontalCenter: parent.horizontalCenter
                   Rectangle{
                       id: rec
                       width: 20
                       height: 20
                       anchors.verticalCenter: parent.verticalCenter
                       anchors.horizontalCenter: parent.horizontalCenter
                       color: "red"
                       radius: 10
                   }
                   MouseArea{
                       anchors.fill: parent
                       onPressedChanged: pressed? rec.color="blue": rec.color="red"

                       onClicked: {
                           console.log("CENTRAL")
                       }
                   }


               }
           }

           MatTableCard{
               anchors.left: parent.left
               anchors.right: parent.right
               anchors.margins: Style.panelsMargins
               model: pnpos.getImgModel()
           }

           MTK_HSeparator{}

           MTK_Label{
               text: "Расчёт точек объекта"
               anchors.left: parent.left
               anchors.leftMargin: Style.panelsMargins*2
               horizontalAlignment: Text.AlignLeft
               height: Style.cardHeight
               color: Style.currentTheme.accent
           }

           MTK_HSeparator{}

           MatTableCard{
               anchors.left: parent.left
               anchors.right: parent.right
               anchors.margins: Style.panelsMargins
               model: pnpos.getObjModel()
           }

           MTK_HSeparator{}

        }
    }
}
