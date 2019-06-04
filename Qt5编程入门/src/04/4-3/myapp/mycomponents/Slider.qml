import QtQuick.Controls 1.2

Slider {
    maximumValue : 100
    minimumValue : 0

    onValueChanged: print(value)
}
