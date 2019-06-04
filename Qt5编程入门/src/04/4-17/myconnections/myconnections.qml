import QtQuick 2.2

Rectangle {
    id: rect; width: 100; height: 100

    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }

    Connections {
        target: mouseArea
        onClicked: rect.color = "red"
    }
}


