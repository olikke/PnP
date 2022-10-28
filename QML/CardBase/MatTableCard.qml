import QtQuick 2.9

import "qrc:/QML/ElementBase"
import "qrc:/QML"

Item{
    height: root.height

    property alias model: root.model
    GridView{
        id: root
        width: parent.width
        height: cellHeight*model.rowCount()
        cellWidth:width/model.columnCount()
        cellHeight:Style.btnHeight*0.8
        Component.onCompleted: console.log(root.count)


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
