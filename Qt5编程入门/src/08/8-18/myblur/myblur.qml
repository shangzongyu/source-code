import QtQuick 2.2
import QtGraphicalEffects 1.0

Item {
    width: 300; height: 300

    Image {
        id: bug; source: "images/bug.png"
        sourceSize: Qt.size(parent.width, parent.height)
        smooth: true; visible: false
    }

    LinearGradient {
        id: mask; anchors.fill: bug; visible: false
        gradient: Gradient {
            GradientStop { position: 0.2; color: "#ffffffff" }
            GradientStop { position: 0.5; color: "#00ffffff" }
        }
        start: Qt.point(0, 0); end: Qt.point(300, 0)
    }

    MaskedBlur {
        anchors.fill: bug; source: bug
        maskSource: mask; radius: 16; samples: 24
    }
}



