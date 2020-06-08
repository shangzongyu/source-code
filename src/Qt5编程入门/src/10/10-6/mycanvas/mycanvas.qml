import QtQuick 2.2

Canvas {
    id: mycanvas
    width:300; height: 250
    onPaint: {
        var ctx = getContext("2d");
        ctx.lineWidth = 2

        ctx.beginPath()
        ctx.moveTo(0, 60)
        ctx.lineTo(240, 60)
        ctx.stroke()

        ctx.beginPath()
        ctx.moveTo(30, 60)
        ctx.arc(30, 60, 20, 0, -Math.PI / 2, true)
        ctx.stroke()

        ctx.beginPath()
        ctx.moveTo(90, 60)
        ctx.arc(90, 60, 20, 0, Math.PI, true)
        ctx.stroke()

        ctx.beginPath()
        ctx.moveTo(150, 60)
        ctx.arc(150, 60, 20, 0, -3 * Math.PI / 2, true)
        ctx.stroke()

        ctx.beginPath()
        ctx.moveTo(210, 60)
        ctx.arc(210, 60, 20, 0, Math.PI * 2, true)
        ctx.stroke()
    }
}
