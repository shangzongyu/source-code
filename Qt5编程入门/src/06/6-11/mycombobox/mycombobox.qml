import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Window 2.1

ApplicationWindow {
    ComboBox {
        id: editableCombo; editable: true
        model: ListModel {
            id: model
            ListElement { text: "Banana"; color: "Yellow" }
            ListElement { text: "Apple"; color: "Green" }
            ListElement { text: "Coconut"; color: "Brown" }
        }
        onAccepted: {
            if (editableCombo.find(currentText) === -1) {
                model.append({text: editText})
                currentIndex = editableCombo.find(editText)
            }
        }
    }
}



