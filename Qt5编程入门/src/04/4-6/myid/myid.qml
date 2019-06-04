import QtQuick 2.2

Row {
    Text {
        id: text1
        text: "Hello World"
    }

    Text { text: text1.text }
}


