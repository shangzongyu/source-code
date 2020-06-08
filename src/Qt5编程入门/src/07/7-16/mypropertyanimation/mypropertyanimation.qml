import QtQuick 2.2

Rectangle {
    width: 100; height: 100
    color: "red"

    SequentialAnimation on color {
        ColorAnimation { to: "yellow"; duration: 1000 }
        ColorAnimation { to: "blue"; duration: 1000 }
    }
}


