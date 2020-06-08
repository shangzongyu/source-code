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
        id: displacement
        anchors.centerIn: parent; source: "images/glass_normal.png"
        sourceSize: Qt.size(parent.width, parent.height)
        smooth: true; visible: false
    }

    Displace {
        anchors.fill: bug; source: bug
        displacementSource: displacement; displacement: 0.2
    }
}

