import QtQuick 2.2
import QtMultimedia 5.0
import QtGraphicalEffects 1.0

Item {
    width: 450; height: 350

    Video {
        id: video; y:50; width: 400; height: 300
        source: "video.wmv"

        MouseArea {
            anchors.fill: parent
            onClicked: video.play()
        }
    }

    FastBlur {
        width: 150; height: 100;
        source: video; radius: 32
    }
}


