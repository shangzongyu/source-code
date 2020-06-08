import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Window 2.1

ApplicationWindow {
    Column {
        ExclusiveGroup { id: group }

        RadioButton {
            text: qsTr("From top")
            exclusiveGroup: group
            checked: true
        }
        RadioButton {
            text: qsTr("From cursor")
            exclusiveGroup: group
        }
    }
}

