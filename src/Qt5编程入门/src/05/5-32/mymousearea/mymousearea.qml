import QtQuick 2.2

Rectangle {
    color: "yellow"
    width: 100; height: 100

    MouseArea {
        anchors.fill: parent
        onClicked: console.log("clicked yellow")
        onDoubleClicked: {
            console.log("double clicked yellow")
            mouse.accepted = false
        }
    }

    Rectangle {
        color: "blue"
        width: 50; height: 50

        MouseArea {
            anchors.fill: parent
            propagateComposedEvents: true
            onClicked: {
                console.log("clicked blue")
                mouse.accepted = false
            }
            onDoubleClicked: {
                console.log("double clicked blue")
                mouse.accepted = false
            }
        }
    }
}
