import QtQuick 2.0

// 对于每一个Button.qml的实例都会加载一个该JavaScript资源的一个实例
import "my_button_impl.js" as Logic

Rectangle {
    id: rect; width: 200; height: 100; color: "red"

    MouseArea {
        id: mousearea
        anchors.fill: parent
        onClicked: Logic.onClicked(rect)
    }
}

