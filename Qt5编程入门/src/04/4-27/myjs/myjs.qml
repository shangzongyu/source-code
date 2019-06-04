import QtQuick 2.2
import "factorial.js" as MathFunctions

Item {
    MouseArea {
        anchors.fill: parent
        onClicked: console.log(MathFunctions.factorial(10))
    }
}



