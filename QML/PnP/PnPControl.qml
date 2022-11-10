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
        contentHeight: control.height+60

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
                model: pnp.getCameraModel()
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
                model: pnp.getDistModel()
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
               source: "qrc:/ASSETS/Chessboard.png"

               Rectangle{
                  anchors.fill: parent
                  anchors.margins: parent.width/6
                  radius: parent.width/3
                  border.color: Style.currentTheme.accent
                  border.width: 3
                  color: "transparent"
               }

               Target{
                   anchors.centerIn: parent
                   number: 0
                   onClick: pnp.pointNumb=number
                   current: number===pnp.pointNumb
               }

               Target{
                   anchors.verticalCenter: parent.verticalCenter
                   anchors.horizontalCenter: parent.horizontalCenter
                   anchors.horizontalCenterOffset: -parent.width/3
                   number: 1
                   onClick: pnp.pointNumb=number
                   current: number===pnp.pointNumb
               }

               Target{
                   anchors.verticalCenter: parent.verticalCenter
                   anchors.horizontalCenter: parent.horizontalCenter
                   anchors.verticalCenterOffset: -parent.width/3
                   number: 2
                   onClick: pnp.pointNumb=number
                   current: number===pnp.pointNumb
               }

               Target{
                   anchors.verticalCenter: parent.verticalCenter
                   anchors.horizontalCenter: parent.horizontalCenter
                   anchors.horizontalCenterOffset: parent.width/3
                   number: 3
                   onClick: pnp.pointNumb=number
                   current: number===pnp.pointNumb
               }

               Target{
                   anchors.verticalCenter: parent.verticalCenter
                   anchors.horizontalCenter: parent.horizontalCenter
                   anchors.verticalCenterOffset: parent.width/3
                   number: 4
                   onClick: pnp.pointNumb=number
                   current: number===pnp.pointNumb
               }

           }

           MatTableCard{
               anchors.left: parent.left
               anchors.right: parent.right
               anchors.margins: Style.panelsMargins
               model: pnp.getImgModel()
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
               model: pnp.getObjModel()
           }

           MTK_HSeparator{}

           ButtonCard{
               enabled: pnp.ready
               iconSource:"qrc:/ASSETS/icon/play.svg"
               labelText:  "РАсчёт положения объекта"
               onClicked: pnp.start()
           }

           MTK_HSeparator{}

           MTK_Label{
               text: "Вектор вращения"
               anchors.left: parent.left
               anchors.leftMargin: Style.panelsMargins*2
               horizontalAlignment: Text.AlignLeft
               height: Style.cardHeight
               color: Style.currentTheme.accent
           }

           MTK_HSeparator{}

           MatTableCard{
               function calc(val) {return val*180/Math.PI}
               anchors.left: parent.left
               anchors.right: parent.right
               anchors.margins: Style.panelsMargins
               model: pnp.getRotation()
               calcValue: calc
           }

           MTK_HSeparator{}

           MTK_Label{
               text: "Вектор смещения"
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
               model: pnp.getTranslation()
           }

           MTK_HSeparator{}

           ButtonCard{
               enabled: pnp.ready
               iconSource:"qrc:/ASSETS/icon/play.svg"
               labelText:  "Обратное проецирование"
               onClicked: pnp.projectPoints()
           }

           MTK_HSeparator{}

           MatTableCard{
               anchors.left: parent.left
               anchors.right: parent.right
               anchors.margins: Style.panelsMargins
               model: pnp.getImgModelCalc()
           }

           MTK_HSeparator{}

           ButtonCard{
               enabled: pnp.pnpReady
               iconSource:"qrc:/ASSETS/icon/rotate.svg"
               labelText:  "Антивращение"
               onClicked: pnp.antiRotate()
           }

           MTK_HSeparator{}

           SliderCard{
               labelText: "Х, пикс"
               from:-720*2
               to: 720*2
               value: 0
               stepSize: 1
               onMove: pnp.setX(value)
           }

           SliderCard{
               labelText: "Y, пикс"
               from: -576*2
               to: 576*2
               value: 0
               stepSize: 1
               onMove: pnp.setY(value)
           }

           MTK_HSeparator{}

           SliderCard{
               labelText: "a1, *100"
               from:-90*10
               to: 90*10
               value: 0
               stepSize: 1
               divider: 10
               onMove: pnp.setA1(value)
           }
           SliderCard{
               labelText: "a2, *100"
               from:-90*10
               to: 90*10
               value: 0
               divider: 10
               stepSize: 1
               onMove: pnp.setA2(value)
           }
           SliderCard{
               labelText: "a3, *100"
               from:-90*10
               to: 90*10
               value: 0
               divider: 10
               stepSize: 1
               onMove: pnp.setA3(value)
           }

        }
    }
}
