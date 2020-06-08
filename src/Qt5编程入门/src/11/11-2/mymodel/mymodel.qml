import QtQuick 2.2

Item {
    width: 200; height: 150

    ListModel {
        id: fruitModel

        ListElement {
            name: "Apple"; cost: 2.45
            attributes: [
                ListElement { description: "Core" },
                ListElement { description: "Deciduous" }
            ]
        }
        ListElement {
            name: "Orange"; cost: 3.25
            attributes: [
                ListElement { description: "Citrus" }
            ]
        }
        ListElement {
            name: "Banana"; cost: 1.95
            attributes: [
                ListElement { description: "Tropical" },
                ListElement { description: "Seedless" }
            ]
        }
    }

    Component {
        id: fruitDelegate
        Item {
            width: 200; height: 50
            Text { id: nameField; text: name }
            Text { text: '$' + cost; anchors.left: nameField.right }
            Row {
                anchors.top: nameField.bottom; spacing: 5
                Text { text: "Attributes:" }
                Repeater {
                    model: attributes
                    Text { text: description }
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: fruitModel.setProperty(index, "cost", cost * 2)
            }
        }
    }

    ListView {
        anchors.fill: parent
        model: fruitModel; delegate: fruitDelegate
    }
}

