import QtQuick 2.2

Flickable {
    width: 150; height: 150
    contentWidth: 300; contentHeight: 300

    rebound: Transition {
        NumberAnimation {
            properties: "x,y"
            duration: 1000
            easing.type: Easing.OutBounce
        }
    }

    Rectangle {
        width: 300; height: 300
        color: "steelblue"
    }

    flickableDirection: Flickable.HorizontalFlick
}


