import QtQuick 2.2

Rectangle {
    id: window
    color: "white"; width: 240; height: 150

    Column {
        anchors.centerIn: parent; spacing: 15

        MyWidget {
            color: "lightblue"
            Component.onCompleted: console.log("1")
        }
        MyWidget {
            focus: true
            color: "palegreen"
            Component.onCompleted: console.log("2")
        }
        MyWidget {
            color: "red"
            Component.onCompleted: console.log("3")
        }
    }
}

