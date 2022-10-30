import QtQuick 2.9

import "qrc:/QML/ElementBase"
import "qrc:/QML"

Item{
    height: root.height

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
            color: Style.currentTheme.background
            radius: Style.unitRadius/2
            MTK_Label{
                anchors.fill: parent
                text: display.toFixed(3)
            }
        }
    }
}
