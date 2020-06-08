import QtQuick 2.2

Item {
    width: 80; height: 370
    ListView {
        id: listview; anchors.fill: parent; anchors.margins: 30
        model: 20; spacing: 5
        clip: true
        delegate: numberDelegate; snapMode: ListView.SnapToItem
        header: Rectangle {
            width: 50; height: 20; color: "#b4d34e"
            Text {anchors.centerIn: parent; text: "header"}
        }
        footer: Rectangle {
            width: 50; height: 20; color: "#797e65"
            Text {anchors.centerIn: parent; text: "footer"}
        }
        highlight: Rectangle {  color: "black"; radius: 5 ; opacity: 0.3; z:5}
        focus: true; keyNavigationWraps :true
        highlightMoveVelocity: 100
    }
    Component {
        id: numberDelegate

        Rectangle {
            id: wrapper; width: 50; height: 50;
            color: ListView.isCurrentItem ? "white" : "lightGreen"
            Text {
                anchors.centerIn: parent; font.pointSize: 15; text: index
                color: wrapper.ListView.isCurrentItem ? "blue" : "white"
            }
        }
    }
}


