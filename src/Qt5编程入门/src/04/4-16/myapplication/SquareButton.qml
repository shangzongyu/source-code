import QtQuick 2.2

Rectangle {
    id: root

    signal activated(real xPosition, real yPosition)
    signal deactivated

    width: 100; height: 100

    MouseArea {
        anchors.fill: parent
        onPressed: root.activated(mouse.x, mouse.y)
        onReleased: root.deactivated()
    }
}
