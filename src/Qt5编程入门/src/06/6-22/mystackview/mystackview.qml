import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Window 2.1

ApplicationWindow {
    width: 800; height: 600

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
                         | Qt.MiddleButton

        onClicked: {
            if (mouse.button === Qt.LeftButton) {
                stackView.push([blueView, greenView, yellowView]);
            } else if (mouse.button == Qt.RightButton) {
                stackView.pop();
            } else {
                stackView.push({item: orangeView, replace: true});
            }
        }
    }

    Rectangle { id: blueView; color: "blue" }
    Rectangle { id: greenView; color: "green" }
    Rectangle { id: yellowView; color: "yellow" }
    Rectangle { id: orangeView; color: "orange" }

    StackView {
        id: stackView; anchors.fill: parent
        initialItem: Item {
            id: redView
            Rectangle { anchors.fill: parent; color: "red" }
        }
    }
}
