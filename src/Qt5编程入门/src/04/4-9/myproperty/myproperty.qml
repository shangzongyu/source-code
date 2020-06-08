import QtQuick 2.2

Rectangle {
    // 使用静态值初始化
    width: 400
    height: 200
    color: "red"
    Rectangle {
        // 使用绑定表达式初始化
        width: parent.width / 2
        height: parent.height
    }
}



