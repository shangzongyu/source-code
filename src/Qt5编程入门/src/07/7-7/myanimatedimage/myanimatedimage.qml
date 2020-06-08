import QtQuick 2.2

Rectangle {
    property int frames
    width: animation.width; height: animation.height + 8

    AnimatedImage { id: animation; source: "animation.gif"}

    Component.onCompleted: {
        frames =animation.frameCount
    }

    Rectangle {
        width: 4; height: 8
        x: (animation.width - width) * animation.currentFrame / frames
        y: animation.height
        color: "red"
    }
}


