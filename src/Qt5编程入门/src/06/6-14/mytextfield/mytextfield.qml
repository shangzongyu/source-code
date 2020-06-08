import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Window 2.1

ApplicationWindow {
    TextField {
        y:10; width: 200
        placeholderText: "Please enter a password";
        echoMode: TextInput.PasswordEchoOnEdit
        validator: IntValidator {bottom: 11; top: 31;}
        onAccepted: console.debug(text)
    }
    TextField {y: 40; width: 200}
}
