import QtQuick 2.2
import QtGraphicalEffects 1.0

Item {
    width: 300; height: 300

    Image {
        id: bug; source: "images/bug.png"
        sourceSize: Qt.size(parent.width, parent.height)
        smooth: true; visible: false
    }

    DirectionalBlur {
        anchors.fill: bug; source: bug
        angle: 90; length: 32; samples: 24
    }
}


