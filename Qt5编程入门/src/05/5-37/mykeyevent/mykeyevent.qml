import QtQuick 2.2

Item {
    focus: true
    Keys.onPressed: {
        if (event.key == Qt.Key_Left) {
            console.log("move left");
            event.accepted = true;
        }
    }
    Keys.onReturnPressed: console.log("Pressed return");
}
