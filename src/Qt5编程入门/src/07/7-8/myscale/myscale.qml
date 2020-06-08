import QtQuick 2.2

Rectangle {
    color: "grey"
    width: 100; height: 100
    Rectangle {
        color: "blue"
        width: 25; height: 25
    }
    Rectangle {
        color: "red"
        x: 25; y: 25; width: 25; height: 25
        scale: 1.6
    }
}
