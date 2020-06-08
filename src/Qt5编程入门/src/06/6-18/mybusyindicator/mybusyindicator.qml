import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Window 2.1

ApplicationWindow {
    BusyIndicator {
        id: busyIndicator; running: true
    }
    MouseArea {
        anchors.fill: parent
        onClicked: busyIndicator.running = false
    }
}
