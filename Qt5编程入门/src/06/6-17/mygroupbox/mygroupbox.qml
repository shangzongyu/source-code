import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Window 2.1

ApplicationWindow {
    width: 300; height: 200
    GroupBox {
        title: qsTr("Group 2"); checkable: true
        x: 10; y: 10; width: 200; height: 100
        Column {
            spacing: 2
            CheckBox { text: qsTr("Update system") }
            CheckBox { text: qsTr("Update applications") }
            CheckBox { text: qsTr("Update documentation") }
        }
    }
}
