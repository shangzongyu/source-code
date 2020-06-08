import QtQuick 2.2

Rectangle {
    width: 400; height: 240; color: "black"

    Grid {
        x: 5; y: 5
        rows: 5; columns: 5; spacing: 10

        Repeater {
            model: 12
            Rectangle {
                width: 70; height: 70; color: "lightgreen"

                Text {
                    text: index; font.pointSize: 30
                    anchors.centerIn: parent
                }
            }
        }
    }
}

