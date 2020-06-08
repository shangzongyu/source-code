import QtQuick 2.2

Item {
    property Component mycomponent: comp1

    QtObject {
        id: internalSettings
        property color color: "green"
    }

    Component {
        id: comp1
        Rectangle { color: internalSettings.color; width: 400; height: 50 }
    }
}
