import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Window 2.1

ApplicationWindow {
    ProgressBar {
        id: progressBar
        minimumValue: 0; maximumValue: 100
    }
    Timer {
        interval: 100; running: true; repeat: true
        onTriggered: progressBar.value++;
    }
}
