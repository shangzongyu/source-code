import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Window 2.1

ApplicationWindow {
    ComboBox {
        width: 200; currentIndex: 2
        model: ListModel {
            id: cbItems
            ListElement { text: "Banana"; color: "Yellow" }
            ListElement { text: "Apple"; color: "Green" }
            ListElement { text: "Coconut"; color: "Brown" }
        }
        onCurrentIndexChanged:
            console.debug(cbItems.get(currentIndex).text + ", "
                          + cbItems.get(currentIndex).color)
    }
}
