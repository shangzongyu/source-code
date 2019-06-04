import QtQuick 2.2

Rectangle {
    id: container; width: 80; height: 300

    ListModel {
        id: nameModel
        ListElement { name: "Alice"; team: "Crypto" }
        ListElement { name: "Bob"; team: "Crypto" }
        ListElement { name: "Jane"; team: "QA" }
        ListElement { name: "Victor"; team: "QA" }
        ListElement { name: "Wendy"; team: "Graphics" }
    }

    ListView {
        anchors.fill: parent; model: nameModel
        delegate: Text { text: name; font.pixelSize: 18 }
        section.property: "team"
        section.criteria: ViewSection.FullString
        section.delegate: sectionHeading
    }

    Component {
        id: sectionHeading
        Rectangle {
            width: container.width; height: childrenRect.height
            color: "lightsteelblue"

            Text {
                text: section; font.bold: true; font.pixelSize: 20
            }
        }
    }
}





