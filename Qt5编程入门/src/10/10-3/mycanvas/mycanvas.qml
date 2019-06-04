import QtQuick 2.2

Canvas {
    id: mycanvas
    width: 200; height: 200
    onPaint: {
        var ctx = getContext("2d");
        ctx.fillStyle = "green"
        ctx.strokeStyle = "blue"
        ctx.lineWidth = 2
        ctx.font = "bold 50px Arial"

        var text = "qter.org";
        context.fillText(text, 10, 80)
        context.strokeText(text, 10, 150)
    }
}
