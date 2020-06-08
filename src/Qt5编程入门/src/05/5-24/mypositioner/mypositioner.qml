import QtQuick 2.2

Grid {
    Repeater {
        model: 16

        Rectangle {
            id: rect
            width: 30; height: 30
            border.width: 1
            color: Positioner.isFirstItem ?
                       "yellow" : "lightsteelblue"

            Text { text: rect.Positioner.index }
        }
    }
}
