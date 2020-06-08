import QtQuick 2.2

Rectangle {
   id: myItem
   signal message(string msg)

   width: 100; height: 100

   MouseArea {
       anchors.fill: parent
       onClicked: myItem.message("clicked!")
   }
}
