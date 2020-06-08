import QtQuick 2.2

Rectangle {
    id: window
    width: 120; height: 120
    color: "black"

    Rectangle { id: myRect; width: 50; height: 50; color: "red" }

    states: State {
        name: "reanchored"

        AnchorChanges {
            target: myRect
            anchors.top: window.top
            anchors.bottom: window.bottom
        }
        PropertyChanges {
            target: myRect
            anchors.topMargin: 10
            anchors.bottomMargin: 10
        }
    }

    MouseArea {
        anchors.fill: parent;
        onClicked: window.state = "reanchored"
    }
}
