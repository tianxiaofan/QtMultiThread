import QtQuick 2.0
import DataCruncher 1.0

Rectangle {
    color: "#555555"
    ListView{
        id: list
        anchors.fill: parent
        model:DataController.filteredValues
        visible: count
        delegate: Text{
            text: label + value
        }

    }
    Text{
        anchors.centerIn: parent
        text: "No fond"
        visible: !list.count
    }

}
