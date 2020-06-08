import QtQuick 2.2

Rectangle {
    id: rect
    width: 100; height: 100
    color: "red"

    PropertyAnimation on x { to: 100 }
    PropertyAnimation on y { to: 100 }
}

