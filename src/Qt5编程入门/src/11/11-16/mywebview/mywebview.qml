import QtQuick 2.2
import QtQuick.Controls 1.2
import QtWebKit 3.0

ApplicationWindow {
    id: window; width: 1024; height: 500

    ScrollView {
        anchors.fill: parent
        WebView {
            id: webview; url: "http://qter.org"
            anchors.fill: parent
            BusyIndicator {
                id: busyIndicator; anchors.centerIn: parent
                running: webview.loadProgress < 10
            }
        }
    }

    ProgressBar {
        width: parent.width; anchors.bottom: parent.bottom
        minimumValue: 0; maximumValue: 100
        value: webview.loadProgress
        visible: value ==100? false : true
    }
}
