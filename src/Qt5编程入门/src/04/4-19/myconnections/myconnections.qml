import QtQuick 2.2

Rectangle {
    id: forwarder
    width: 100; height: 100

    signal send()
    onSend: console.log("Send clicked")

    MouseArea {
        id: mousearea
        anchors.fill: parent
        onClicked: console.log("MouseArea clicked")
    }

    Component.onCompleted: {
        mousearea.clicked.connect(send)
    }
}



