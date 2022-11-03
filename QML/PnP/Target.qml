import QtQuick 2.0

import "qrc:/QML"

Item {
    width: 40
    height: width
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
        property int minSize:parent.width*0.75
        property int maxSize:parent.width
        width: minSize
        height: width
        radius: width/2
        color: "transparent"
        anchors.centerIn: parent
        Image{
            visible: current
            anchors.fill: parent
            source: "qrc:/ASSETS/icon/ads_click.svg"
        }
    }

    SequentialAnimation{
        id: targetAnimation
        loops: Animation.Infinite
        NumberAnimation {
            target: rec
            properties: "width"
            from:  rec.minSize
            to: rec.maxSize
            duration: Style.animationDuration*4
            easing.type: Easing.Linear
        }
        NumberAnimation {
            target: rec
            properties: "width"
            from:  rec.maxSize
            to: rec.minSize
            duration: Style.animationDuration*4
        }
    }

    MouseArea{
        anchors.fill: parent
        onClicked: click()
    }

}
