import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Window 2.1

ApplicationWindow {
    width: 200; height: 200
    ScrollView {
        anchors.fill: parent
        Image { source: "screen.png" }
    }
}
