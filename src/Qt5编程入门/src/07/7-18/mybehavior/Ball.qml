import QtQuick 2.2

Rectangle {
    width: 75; height: 75; radius: width
    id: ball
    color: "lightsteelblue"

    Behavior on x {
        NumberAnimation {
            id: bouncebehavior
            easing {
                type: Easing.OutElastic
                amplitude: 1.0
                period: 0.5
            }
        }
    }
    Behavior on y {
        animation: bouncebehavior
    }
    Behavior {
        ColorAnimation { target: ball; duration: 300 }
    }
}
