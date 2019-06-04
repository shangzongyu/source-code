import QtQuick 2.2

Canvas {
    id: mycanvas
    width: 200; height: 200
    onPaint: {
        var ctx = getContext("2d")
        ctx.fillStyle = "black"
        ctx.fillRect(10, 10, 50, 50) // 第一个矩形
        ctx.save()
        ctx.fillStyle = ctx.createPattern("red", Qt.Dense1Pattern)
        ctx.fillRect(70, 10, 50, 50) // 第二个矩形
        ctx.restore()
        ctx.fillRect(130, 10, 50, 50) // 第三个矩形
    }
}
