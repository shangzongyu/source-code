import QtQuick 2.2

Item {
    width: 200; height: 200

    Loader {
        anchors.fill: parent
        sourceComponent: rect
    }

    Component {
        id: rect
        Rectangle {
            width: 50
            height: 50
            color: "red"
        }
    }
}
