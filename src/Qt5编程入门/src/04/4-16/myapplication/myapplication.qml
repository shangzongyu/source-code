import QtQuick 2.2

SquareButton {
    onActivated: console.log("Activated at "
                             + xPosition + "," + yPosition)
    onDeactivated: console.log("Deactivated!")
}


