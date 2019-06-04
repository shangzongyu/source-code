import QtQuick 2.2
import QtGraphicalEffects 1.0

Item {
    width: 300; height: 300

    Rectangle { anchors.fill: parent; color: "black" }

    RectangularGlow {
        anchors.fill: rect; glowRadius: 20
        spread: 0.4; color: "white"
        cornerRadius: rect.radius + glowRadius
    }

    Rectangle {
        id: rect; anchors.centerIn: parent
        color: "black"; radius: 25
        width: Math.round(parent.width / 1.5)
        height: Math.round(parent.height / 2)
    }
}

