import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.1

ApplicationWindow{
    id: window; width: 300; height: 300
    Button {
        width: 100; height: 50; text: "File Dialog"
        anchors.centerIn: parent
        onClicked: fileDialog.open()
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        nameFilters: [ "Image files (*.jpg *.png)", "All files (*)" ]
        folder: ".."
        onAccepted: { window.title = fileDialog.fileUrl }
        onRejected: { console.log("Canceled") }
    }
}

