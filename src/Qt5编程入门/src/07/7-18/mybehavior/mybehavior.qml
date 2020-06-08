import QtQuick 2.2

Item {
    width: 400; height: 400

    Ball { id: ball }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            ball.color = Qt.tint(ball.color, "#10FF0000")
            ball.x += 20
            ball.y += 20
        }
    }
}

