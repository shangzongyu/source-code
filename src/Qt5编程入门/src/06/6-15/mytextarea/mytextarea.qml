import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Window 2.1

ApplicationWindow {
    TextArea {
        id: textArea_1; width: 240; height: 100
        textFormat: TextEdit.RichText
        font.pointSize: 13
        text: "<b>Hello</b> <i>World!</i>"
    }
    TextArea {
        id: textArea_2; y:100; width: 240
        textFormat: TextEdit.PlainText
        text: "<b>Hello</b> <i>World!</i>"
    }
}
