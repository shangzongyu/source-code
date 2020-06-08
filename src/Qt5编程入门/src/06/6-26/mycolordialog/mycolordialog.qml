import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.1

ApplicationWindow{
    id: window; width: 300; height: 300
    Button {
        width: 100; height: 50; text: "Color Dialog"
        anchors.centerIn: parent
        onClicked: colorDialog.open()
    }

    ColorDialog {
        id: colorDialog
        title: "Please choose a color"
        onAccepted: { window.color = color }
        onRejected: { console.log("Canceled")}
    }
}

