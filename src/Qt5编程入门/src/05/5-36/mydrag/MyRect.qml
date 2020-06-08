import QtQuick 2.2

Rectangle {
    id: rect
    width: 20; height: 20

    Drag.active: dragArea.drag.active
    Drag.hotSpot.x: 10
    Drag.hotSpot.y: 10
    Drag.source: rect
    MouseArea {
        id: dragArea
        anchors.fill: parent
        drag.target: parent
    }
}

