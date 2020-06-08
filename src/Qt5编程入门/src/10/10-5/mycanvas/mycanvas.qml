import QtQuick 2.2

Canvas {
    id: mycanvas
    width:300; height: 250
    onPaint: {
        var ctx = getContext("2d");
        ctx.strokeStyle = "green"
        ctx.lineWidth = 4

        ctx.beginPath()
        ctx.moveTo(120, 60)
        ctx.lineTo(20, 180)
        ctx.lineTo(220, 180)
        ctx.closePath()
        ctx.stroke()
    }
}
