import QtQuick 2.2

Canvas {
    id: mycanvas
    width:400; height: 400
    onPaint: {
        var ctx = getContext("2d")
        var conical = ctx.createConicalGradient(280, 60, Math.PI / 4)
        conical.addColorStop(0, "white")
        conical.addColorStop(0.5, "#FF00FF")
        conical.addColorStop(1, "#333333")
        ctx.fillStyle = conical
        ctx.fillRect(230, 10, 100, 100)
        ctx.strokeRect(230, 10, 100, 100)
    }
}
