import QtQuick 2.2
import QtQml.Models 2.1

Rectangle {
    width: 200; height: 100

    DelegateModel {
        id: delegateModel
        model: ListModel {
            ListElement { name: "Apple" }
            ListElement { name: "Orange" }
            ListElement { name: "Banana" }
        }

        groups: [
            DelegateModelGroup { name: "selected" }
        ]

        delegate: Rectangle {
            id: item; height: 25; width: 200
            Text {
                text: {
                    var text = "Name: " + name
                    if (item.DelegateModel.inSelected)
                        text += " (" + item.DelegateModel.selectedIndex + ")"
                    return text;
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: item.DelegateModel.inSelected = !item.DelegateModel.inSelected
            }
        }
    }

    ListView {
        anchors.fill: parent; model: delegateModel; focus: true
        Keys.onPressed: {
            if (event.key == Qt.Key_S)  delegateModel.filterOnGroup = "selected"
            else delegateModel.filterOnGroup = ""
        }
    }
}

