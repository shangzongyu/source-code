import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.1

ApplicationWindow{
    id: window; width: 300; height: 300
    Button {
        width: 100; height: 50; text: "Font Dialog"
        anchors.centerIn: parent
        onClicked: fontDialog.open()
    }

    FontDialog {
        id: fontDialog
        title: "Please choose a font"
        font: Qt.font({ family: "Arial", pointSize: 24, weight: Font.Normal })
        onAccepted: { console.log("You chose: " + fontDialog.font) }
        onRejected: { console.log("Canceled") }
    }
}
