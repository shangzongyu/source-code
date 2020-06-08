import QtQuick 2.2

ListView {
    width: 240; height: 320; model: 3; focus: true
    delegate: Rectangle {
        width: 240; height: 30
        color: ListView.isCurrentItem ? "red" : "yellow"
    }
}


