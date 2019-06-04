import QtQuick 2.2

Rectangle {
    width: 200; height: 200

    ListModel {
        id: model
        ListElement { name: "Jim"; portrait: "icon.png" }
        ListElement { name: "John"; portrait: "icon.png" }
        ListElement { name: "Bill"; portrait: "icon.png" }
        ListElement { name: "Sam"; portrait: "icon.png" }
    }

    GridView {
        id: grid; width: 200; height: 200
        cellWidth: 80; cellHeight: 80
        model: model; delegate: contactDelegate
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        focus: true
    }

    Component {
        id: contactDelegate
        Item {
            width: grid.cellWidth; height: grid.cellHeight
            Column {
                anchors.fill: parent
                Image { source: portrait; anchors.horizontalCenter:
                                                 parent.horizontalCenter }
                Text { text: name; anchors.horizontalCenter:
                                                 parent.horizontalCenter }
            }
        }
    }
}





