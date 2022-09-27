import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import DataCruncher 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    FpsCounter{
        anchors.right: parent.right
    }
    Row{
        id: buttons
        spacing: 10
        x : 10
        Button{
            text: "Start"
            onClicked:DataController.start()
        }
        Button{
            text: "Stop"
            onClicked: DataController.stop()
        }
    }

    Row{
        anchors.top: buttons.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        spacing: 10

        ListView{
            width: parent.width/2
            height: parent.height/2
            anchors.margins: 10
            model: DataController.values
            delegate: Text {
                text: label + value
            }
        }

        MatchesWindow{
            width: parent.width/2
            height: parent.height
        }
    }


}
