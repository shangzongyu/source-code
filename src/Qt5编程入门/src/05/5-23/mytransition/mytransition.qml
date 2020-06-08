import QtQuick 2.2

Column {
    spacing: 2

    Rectangle { color: "red"; width: 50; height: 50 }
    Rectangle { id: greenRect; color: "green";
                   width: 20; height: 50 }
    Rectangle { color: "blue"; width: 50; height: 20 }

    move: Transition {
        NumberAnimation { properties: "x,y"; duration: 1000 }
    }

    focus: true
    Keys.onSpacePressed: greenRect.visible = !greenRect.visible
}

