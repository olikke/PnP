import QtQuick 2.9

import "qrc:/QML"

Text{
    id: root

    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignHCenter
    font.family: Style.robotoCondensed
    font.capitalization: Font.AllUppercase
    font.bold: true
    font.pointSize: 12
    color: Style.currentTheme.foreground
    wrapMode: Text.WordWrap
}
