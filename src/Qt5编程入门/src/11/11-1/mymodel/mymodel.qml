import QtQuick 2.2

Item {
    width: 200; height: 50

    ListModel {
        id: myModel
        ListElement { type: "Dog"; age: 8 }
        ListElement { type: "Cat"; age: 5 }
    }

    Component {
        id: myDelegate
        Text { text: type + ", " + age; font.pointSize: 12 }
    }

    ListView {
        anchors.fill: parent
        model: myModel; delegate: myDelegate
    }
}

