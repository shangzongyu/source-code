import QtQuick 2.2

Rectangle {
    width: 360; height: 360

    MyLabel {
        anchors.centerIn: parent
        Text { text: "world!" }
    }
}

