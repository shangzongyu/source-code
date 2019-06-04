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

    RadialGradient {
        anchors.fill: butterfly; source: butterfly
        verticalRadius: 100; angle: 30
        gradient: Gradient {
            GradientStop { position: 0.0; color: "white" }
            GradientStop { position: 0.5; color: "black" }
        }
    }
}


