import QtQuick 2.9

import "qrc:/QML/ElementBase"
import "qrc:/QML"

Column{
    height: implicitHeight

    Rectangle{
        anchors.left: parent.left
        anchors.right: parent.right
        height: (Style.cardHeight-Style.btnHeight)/2
        color:"transparent"
    }

    //in Qt5.11 we dont have qml TableView. So we use GridView with some bike
    property alias model: root.model
    GridView{
        id: root
        width: parent.width
        height: cellHeight*model.rowCount()/model.columnCount()
        cellWidth:width/model.columnCount()
        cellHeight:Style.btnHeight*0.8

        delegate:Rectangle {
            width:root.cellWidth-Style.connectionWidth
            height: root.cellHeight-Style.connectionWidth
            color: Style.currentTheme.primary
            border.color: Style.currentTheme.background
            border.width: 2
            radius: Style.unitRadius/2
            MTK_Label{
                anchors.fill: parent
                text: display.toFixed(3)
            }
        }
    }

    Rectangle{
        anchors.left: parent.left
        anchors.right: parent.right
        height: (Style.cardHeight-Style.btnHeight)/2
        color:"transparent"
    }
}
