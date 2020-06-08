import QtQuick 2.2
import QtMultimedia 5.0

Text {
    text: "Click Me!";
    font.pointSize: 24;
    width: 150; height: 50;

    SoundEffect {
        id: playSound
        source: "soundeffect.wav"
    }
    MouseArea {
        id: playArea; anchors.fill: parent
        onPressed: { playSound.play() }
    }
}


