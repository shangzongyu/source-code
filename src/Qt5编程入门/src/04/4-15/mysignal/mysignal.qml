import QtQuick 2.2

Rectangle {
    id: rect
    width: 100; height: 100

    MouseArea {
        anchors.fill: parent
        onClicked: {
            rect.color = Qt.rgba(Math.random(),
                                 Math.random(), Math.random(), 1);
        }
    }
}

