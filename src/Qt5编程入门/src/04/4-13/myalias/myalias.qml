import QtQuick 2.2

Rectangle {
    id: coloredrectangle
    property alias color: bluerectangle.color
    color: "red"

    Rectangle {
        id: bluerectangle
        color: "#1234ff"
    }

    Component.onCompleted: {
        console.log(coloredrectangle.color) // #1234ff
        setInternalColor()
        console.log(coloredrectangle.color) // #111111
        coloredrectangle.color = "#884646"
        console.log(coloredrectangle.color) // #884646
    }

    // 内部函数访问内部属性
    function setInternalColor() {
        color = "#111111"
    }
}


