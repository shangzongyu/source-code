import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Window 2.0

ApplicationWindow {
    SpinBox {
        minimumValue: -5; maximumValue: 10
        prefix: "Today: "; suffix: " Degree"
        decimals: 1; stepSize: 0.1
    }
}
