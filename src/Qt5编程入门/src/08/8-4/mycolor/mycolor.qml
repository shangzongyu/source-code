import QtQuick 2.2
import QtGraphicalEffects 1.0

Item {
    width: 300; height: 300

    Image {
        id: bug; source: "images/bug.png"
        sourceSize: Qt.size(parent.width, parent.height)
        smooth: true; visible: false
    }

    Colorize {
        anchors.fill: bug; source: bug
        hue: 0.0; saturation: 0.5; lightness: -0.2
    }
}


