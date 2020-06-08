import QtQuick 2.2

Rectangle {
    // 只声明，不初始化
    property list<Rectangle> siblingRects

    // 声明并且初始化
    property list<Rectangle> childRects: [
        Rectangle { color: "red" },
        Rectangle { color: "blue"}
    ]

    MouseArea {
        anchors.fill:parent
        onClicked: {
            for (var i = 0; i < childRects.length; i++)
                console.log("color", i, childRects[i].color)
        }
    }
}



