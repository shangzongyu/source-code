import QtQuick 2.2

Rectangle {
    property alias buttonText: textItem.text
    width: 100; height: 30; color: "yellow"
    Text { id: textItem }
}

