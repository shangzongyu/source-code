import QtQuick 2.2

Rectangle {
    width: 400
    height: 200

    Rectangle {
        color: "gold"
        width: 400; height: 40
    }
    Rectangle {
        color: "transparent"
        y: 40; width: 400; height: 40
    }
    Rectangle {
        color: "#FFA500"
        y: 80; width: 400; height: 40
    }
    Rectangle {
        color: "#800000FF"
        y: 120; width: 400; height: 40
    }
    Rectangle {
        color: Qt.tint("blue", "#55FF0000")
        y: 160; width: 400; height: 40
    }
}

