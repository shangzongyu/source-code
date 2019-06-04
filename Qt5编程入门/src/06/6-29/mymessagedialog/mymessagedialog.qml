import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.1

ApplicationWindow{
    id: window; width: 300; height: 300
    Button {
        width: 100; height: 50; text: "Message Dialog"
        anchors.centerIn: parent
        onClicked: messageDialog.open()
    }

    MessageDialog {
        id: messageDialog
        title: "May I have your attention please"
        text: "It's so cool that you are using Qt Quick."
        detailedText: "this is the detailed text!"
        icon: StandardIcon.Question
        standardButtons: StandardButton.Yes | StandardButton.Help
                         | StandardButton.Open
        onYes: { console.log("yes.") }
        onHelp: { console.log("help.") }
        onAccepted: { console.log("open.") }
    }
}
