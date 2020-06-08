import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Window 2.1

ApplicationWindow {
    width: 300; height: 200

    ListModel {
        id: libraryModel
        ListElement{ title: "A Masterpiece" ; author: "Gabriel" }
        ListElement{ title: "Brilliance"    ; author: "Jens" }
        ListElement{ title: "Outstanding"   ; author: "Frederik" }
    }

    TableView {
        anchors.fill: parent; model: libraryModel
        TableViewColumn{ role: "title"  ; title: "Title" ; width: 100 }
        TableViewColumn{ role: "author" ; title: "Author" ; width: 200 }

        itemDelegate: Item {
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                color: styleData.selected? "red":"blue"
                font.pointSize: 10
                text: styleData.row == 2? "myrow" : styleData.value
            }
        }

        onClicked: console.debug(row)
    }
}



