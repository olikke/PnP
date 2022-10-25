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
                    text: "Выбрать изображения"
                    color: Style.currentTheme.accent
                }


                MTK_RoundButton{
                    text: "Открыть папку"
                    onClicked: openFileDialog()
                }
            }

            MTK_HSeparator{opacity: 1}

            Column{
                id: findChessboardCorners
                anchors.left: parent.left
                anchors.right: parent.right
                height: implicitHeight
                anchors.margins: Style.panelsMargins
                spacing: Style.panelsMargins

                MTK_Label{
                    text: "Поиск и отображение углов"
                    color: Style.currentTheme.accent
                }
            }
        }
    }
}
