import QtQuick 2.2

Canvas {
    id: mycanvas
    width:400; height: 400
    onPaint: {
        var ctx = getContext("2d")
        var radial = ctx.createRadialGradient(140, 70, 30, 170, 50, 55)
        radial.addColorStop(0, "white")
        radial.addColorStop(0.5, "#FF00FF")
        radial.addColorStop(1, "#333333")
        ctx.fillStyle = radial
        ctx.fillRect(120, 10, 100, 100)
        ctx.strokeRect(120, 10, 100, 100)
    }
}
