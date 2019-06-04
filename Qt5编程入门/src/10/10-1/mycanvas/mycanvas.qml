import QtQuick 2.2

Canvas {
    id: mycanvas
    width: 200; height: 200
    onPaint: {
        var ctx = getContext("2d");
        ctx.fillStyle = "green" // 设置填充颜色为绿色
        ctx.strokeStyle = "blue" // 设置边线颜色为蓝色
        ctx.lineWidth = 4 // 设置边线宽度为4px
        ctx.lineJoin = "round"

        ctx.fillRect(20, 20, 160, 160)
        ctx.clearRect(30, 30, 140, 140)
        ctx.strokeRect(20, 20, 80, 80)
    }
}
