import QtQuick 2.0

import "qrc:/QML"

Item {
    width: 40
    height: width
    property bool showIcon: true
    property bool current: false
    onCurrentChanged: {
        current? targetAnimation.start() : targetAnimation.stop()
        if  (!current) rec.width=width*0.75
    }

    property int number: -1
    onNumberChanged: {
        switch (number) {
        case 0: rec.color="#f44336"; break;
        case 1: rec.color="#9c27b0"; break;
        case 2: rec.color="#7cb342"; break;
        case 3: rec.color="#ffeb3b"; break;
        case 4: rec.color="#f57c00"; break;
        }
    }

    signal click()
    Rectangle{
        id: rec
        width: parent.width*0.75
        height: width
        radius: width/2
        color: "transparent"
        anchors.centerIn: parent
        Image{
            visible: showIcon & current
            anchors.fill: parent
            source: "qrc:/ASSETS/icon/ads_click.svg"
        }
    }

    SequentialAnimation{
        id: targetAnimation
        NumberAnimation {
            target: rec
            loops: Animation.Infinite
            properties: "width"
            from:  width*0.75
            to: width*1.25
            duration: Style.animationDuration*4
            easing.type: Easing.Linear
        }
        NumberAnimation {
            target: rec
            loops: Animation.Infinite
            properties: "width"
            from:  width*1.25
            to: width*0.75
            duration: Style.animationDuration*4
        }
    }

    MouseArea{
        anchors.fill: parent
        onPressedChanged: rec.width=pressed?parent.width: parent.width*0.75
        onClicked: click()
    }

}
