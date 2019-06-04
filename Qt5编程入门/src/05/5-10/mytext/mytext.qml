import QtQuick 2.2

Column {
    Text {
        font.pointSize: 24
        text: "<b>Hello</b> <i>World!</i>"
    }
    Text {
        font.pointSize: 24; textFormat: Text.RichText
        text: "<b>Hello</b> <i>World!</i>"
    }
    Text {
        font.pointSize: 24; textFormat: Text.PlainText
        text: "<b>Hello</b> <i>World!</i>"
    }
}

