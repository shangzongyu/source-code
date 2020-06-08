import QtQuick 2.2

Canvas {
    id: mycanvas
    width:400; height: 400
    onPaint: {
        var ctx = getContext("2d")
        ctx.lineWidth = 2

        var linear = ctx.createLinearGradient(10, 10, 100, 10)
        linear.addColorStop(0, "white")
        linear.addColorStop(0.5, "#FF00FF")
        linear.addColorStop(1, "#333333")
        ctx.fillStyle = linear
        ctx.fillRect(10, 10, 100, 100)
        ctx.strokeRect(10, 10, 100, 100)
    }
}
