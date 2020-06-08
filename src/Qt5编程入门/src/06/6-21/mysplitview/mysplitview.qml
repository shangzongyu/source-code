import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

ApplicationWindow {
    width: 400; height: 200

    SplitView {
        anchors.fill: parent
        orientation: Qt.Horizontal

        Rectangle {
            width: 200; color: "gray"
            Layout.maximumWidth: 300
        }
        Rectangle {
            id: centerItem; color: "darkgray"
            Layout.minimumWidth: 50
            Layout.fillWidth: true
        }
        Rectangle {
            width: 200; color: "gray"
        }
    }
}

