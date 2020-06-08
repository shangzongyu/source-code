import QtQuick 2.2

Rectangle {
    id: page
    width: 360
    height: 360
    color: "#333333"

    Image {
        id: icon
        x: 10
        y: 20
        width: 50
        height: 50
        source: "qt-logo.png"
    }

    Rectangle {
        id: topLeftRect
        x: 20
        y: 40
        width: 64
        height: 64
        color: "#00000000"
        radius: 6
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 20
        border.color: "#808080"

        MouseArea {
            id: mouseArea1
            anchors.fill: parent
            onClicked: page.state = ''
        }
    }

    Rectangle {
        id: middleRightRect
        x: 23
        y: 41
        width: 64
        height: 64
        color: "#00000000"
        radius: 6
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 10
        MouseArea {
            id: mouseArea2
            anchors.fill: parent
            onClicked: page.state = 'State1'
        }
        border.color: "#808080"
    }

    Rectangle {
        id: bottomLeftRect
        y: 35
        width: 64
        height: 64
        color: "#00000000"
        radius: 6
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        MouseArea {
            id: mouseArea3
            anchors.fill: parent
            onClicked: page.state = 'State2'
        }
        border.color: "#808080"
    }
    states: [
        State {
            name: "State1"

            PropertyChanges {
                target: icon
                x: middleRightRect.x
                y: middleRightRect.y
            }
        },
        State {
            name: "State2"

            PropertyChanges {
                target: icon
                x: bottomLeftRect.x
                y: bottomLeftRect.y
            }
        }
    ]

    transitions: [
        Transition {
            from: "*"; to: "State1"
            NumberAnimation {
                properties: "x,y";
                duration: 1000
            }
        },

        Transition {
            from: "*"; to: "State2"
            NumberAnimation {
                properties: "x,y";
                easing.type: Easing.InOutQuad;
                duration: 2000
            }
        },

        Transition {
            NumberAnimation {
                properties: "x,y";
                duration: 200
            }
        }
    ]

}



