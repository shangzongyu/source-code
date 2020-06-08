import QtQuick 2.2

Rectangle {
    id: banner
    width: 150; height: 100; border.color: "black"

    Column {
        anchors.centerIn: parent
        Text {
            id: code
            text: "Code less."
            opacity: 0.01
        }
        Text {
            id: create
            text: "Create more."
            opacity: 0.01
        }
        Text {
            id: deploy
            text: "Deploy everywhere."
            opacity: 0.01
        }
    }

    MouseArea {
        anchors.fill: parent
        onPressed: playbanner.start()
    }

    SequentialAnimation {
        id: playbanner
        running: false
        NumberAnimation { target: code; property: "opacity";
            to: 1.0; duration: 2000}
        NumberAnimation { target: create; property: "opacity";
            to: 1.0; duration: 2000}
        NumberAnimation { target: deploy; property: "opacity";
            to: 1.0; duration: 2000}
    }
}

