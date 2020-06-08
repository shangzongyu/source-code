import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Window 2.1

ApplicationWindow {
    Slider {
        minimumValue: 0; maximumValue: 100
        stepSize: 1; onValueChanged: console.log(value)
    }
}
