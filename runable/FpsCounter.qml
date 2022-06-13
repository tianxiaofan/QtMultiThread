import QtQuick 2.0

Item {
    id: root

    property int frameCounter: 0
    property int counter: 0
    property int  fps : 0
    property real fpsAvg: 0
    property bool  running: true

    width : 120;
    height : 30
    Text {
        anchors.right: parent.right
        anchors.top: parent.top
        text: "avg " + root.fpsAvg.toFixed(0) + " | " + root.fps + " fps";
    }

    Item{
        property real t
        NumberAnimation on t{
            running: root.running
            from : 0
            to : 1
            duration: 1000
            loops: Animation.Infinite
        }
        onTChanged: {
            frameCounter++
        }
    }

    Timer{
        interval: 1000
        repeat: true
        running: true
        onTriggered: {
            fpsAvg = fpsAvg + (frameCounter - fpsAvg)/++counter
            fps = frameCounter
            frameCounter = 0
        }
    }

}
