import QtQuick 2.2

Item {
    width: 100
    height: 50
    TextInput{
        validator: IntValidator{ bottom: 11; top: 31; }
        focus: true
    }
}
