import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Window 2.0

ApplicationWindow {
    CheckBox {
        width: 140
        text: qsTr("3-state Check Box")
        partiallyCheckedEnabled: true
    }
}

