import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Window 2.1

ApplicationWindow {
    Label {
        textFormat: TextEdit.PlainText
        text: "<b>Hello</b> <i>World!</i>"
        font.pixelSize: 22
        font.italic: true
        color: "steelblue"
    }
}
