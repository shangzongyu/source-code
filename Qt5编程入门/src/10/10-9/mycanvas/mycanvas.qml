import QtQuick 2.2

Canvas {
    id: mycanvas
    width:400; height: 400
    onPaint: {
        var origX = 150, origY = 30
        var cp1x = 20, cp1y = origY
        var cp2x = 300, cp2y = 300
        var x = origX, y = cp2y

        var ctx = getContext("2d")
        ctx.lineWidth = 5

        ctx.beginPath()
        ctx.moveTo(origX, origY)
        ctx.bezierCurveTo(cp1x, cp1y, cp2x, cp2y, x, y)
        ctx.stroke()

        ctx.beginPath()
        ctx.strokeStyle = "lightblue"
        ctx.lineWidth = 1
        // 连接上下文当前点与(cp1x, cp1y)
        ctx.moveTo(origX, origY)
        ctx.lineTo(cp1x, cp1y)
        // 连接终点与(cp2x, cp2y)
        ctx.moveTo(cp2x, cp2y)
        ctx.lineTo(x, y)
        // 绘制基线
        ctx.moveTo(origX, origY)
        ctx.lineTo(x, y)
        ctx.stroke()
    }
}
