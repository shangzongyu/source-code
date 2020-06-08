import QtQuick 2.2

Item {
    width: 320; height: 480

    AnimatedSprite {
        id: sprite; anchors.centerIn: parent
        width: 170; height: 170
        source: "speaker.png"
        frameCount: 60; frameSync: true
        frameWidth: 170; frameHeight: 170
        loops: 3
    }

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: {
            if (!sprite.running) sprite.start();
            if (!sprite.paused) sprite.pause();
            if ( mouse.button == Qt.LeftButton ) {
                sprite.advance(1);
            } else {
                sprite.advance(-1);
            }
        }
    }
}
