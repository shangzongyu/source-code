import QtQuick 2.2
import "script.js" as MyScript

Item {
    id: item
    width: 200; height: 200

    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }

    Component.onCompleted: {
        mouseArea.clicked.connect(MyScript.jsFunction)
    }
}


