import QtQuick 2.2

Item {
    width: 200; height: 200

    MouseArea {
        anchors.fill: parent
        onClicked: label.moveTo(mouse.x, mouse.y)
    }

    Text {
        id: label; text: "Move me!"

        function moveTo(newX, newY) {
            label.x = newX;
            label.y = newY;
        }
    }
}

