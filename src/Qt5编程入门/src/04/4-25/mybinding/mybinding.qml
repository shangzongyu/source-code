import QtQuick 2.2

Item {
    width: 600; height: 600
    Rectangle {
        width: 10; height: width * 2
        color: "red"; anchors.centerIn: parent; focus: true
        Keys.onSpacePressed: height = width * 3

        MouseArea {
            anchors.fill: parent
            onClicked: parent.width += 10
        }
    }
}
