import QtQuick 2.2

Rectangle {
    width: 200
    height: 100
    TextInput{
        focus: true
        onAccepted: {
            text = "hello"
            focus: false
        }
        onEditingFinished: text += " Qt"
    }
}
