import QtQuick 2.2
import QtGraphicalEffects 1.0

Item {
    width: 300; height: 300

    Image {
        id: bug; source: "images/bug.png"
        sourceSize: Qt.size(parent.width, parent.height)
        smooth: true; visible: false
    }

    Image {
        id: mask; source: "images/mask.png"
        sourceSize: Qt.size(parent.width, parent.height)
        smooth: true; visible: false
    }

    ThresholdMask {
        anchors.fill: bug
        source: bug; maskSource: mask
        threshold: 0.45; spread: 0.2
    }
}
