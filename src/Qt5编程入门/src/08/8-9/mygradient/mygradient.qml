import QtQuick 2.2
import QtGraphicalEffects 1.0

Item {
    width: 300; height: 300

    Image {
        id: butterfly
        source: "images/butterfly.png"
        sourceSize: Qt.size(parent.width, parent.height)
        smooth: true; visible: false
    }

    ConicalGradient {
        anchors.fill: parent; source: butterfly
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#F0F0F0" }
            GradientStop { position: 0.5; color: "#000000" }
            GradientStop { position: 1.0; color: "#F0F0F0" }
        }
    }
}


