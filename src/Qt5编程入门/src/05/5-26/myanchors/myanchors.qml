import QtQuick 2.2

Item {
    Rectangle{
        id: rect1
        width: 50; height: 50; color: "blue"
    }
    Rectangle{
        id: rect2
        width: 50; height: 50; color: "red"
        anchors.left: rect1.right
    }
}
