import QtQuick 2.9
import QtQuick.Controls 2.3
import QtGraphicalEffects 1.0

Item{
    id:control

    implicitWidth: 60
    width: !iconOnly ? txt.width + 20 : implicitHeight
    height: implicitHeight
    implicitHeight: 22
    opacity: enabled ? 1 : 0.7
    property string text
    property bool iconOnly: text.length === 0
    property string iconSource: ""
    property int iconSize: 20
    property alias iconRotation: coloroverlay.rotation
    property bool rounded: Style.rounded
    property bool textHorizontalCenter: true
    property color backgroundColor: !invertedColors ? ( Style.isDarkMode ? Style.currentTheme.background : Style.currentTheme.lightBackground ) : Style.currentTheme.primary
    property alias foregroundColor: txt.color
    property alias fontPointSize: txt.font.pointSize
    property bool invertedColors: false
    property bool accentIcon: false
    property color borderColor: "transparent"
    property int borderWidth: 0
    property alias containsMouse: mouseArea.containsMouse

    signal clicked()

    Behavior on opacity {
        NumberAnimation {
            duration: Style.animationDuration;
        }
    }

    Rectangle{
        id:btn

        color: mouseArea.pressed ? Style.currentTheme.accent : mouseArea.hovered ? Qt.lighter(backgroundColor,1.2) : backgroundColor
        radius: rounded ? height/2 : Style.unitRadius/2
        border.color: borderColor
        border.width: borderWidth

        anchors.fill: parent

        Behavior on color{
            ColorAnimation{
                duration: Style.animationDuration;
                easing.type: Easing.InOutQuad
            }
        }
    }

    MTK_Label{
        id:txt

        text: !iconOnly ? control.text : ""
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        anchors.horizontalCenter: textHorizontalCenter? parent.horizontalCenter : coloroverlay.right
        anchors.horizontalCenterOffset: textHorizontalCenter? 0 : 10+txt.implicitWidth/2
        anchors.verticalCenter: parent.verticalCenter
    }

    Image{
        id:image

        width: iconSize
        height: width
        source: iconSource
        sourceSize.width: iconSize
        sourceSize.height: iconSize
        visible: false

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenterOffset: iconOnly? 0: -(control.width/2)+width
    }

    ColorOverlay{
        id: coloroverlay

        source: image
        color: accentIcon? Style.currentTheme.accent : txt.color
        visible: control.iconSource!==""

        anchors.fill: image
    }

    MouseArea{
        id: mouseArea

        hoverEnabled: true
        property bool hovered: false

        anchors.fill: parent

        onClicked: control.clicked()

        onEntered: hovered = true;

        onExited: hovered = false;
    }
}


