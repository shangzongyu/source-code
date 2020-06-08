import QtQuick 2.2

Rectangle {
    SystemPalette { id: myPalette; colorGroup: SystemPalette.Active }

    width: 640; height: 480
    color: myPalette.window

    Text {
        anchors.centerIn: parent
        text: "Hello!"; color: myPalette.windowText
    }
}
