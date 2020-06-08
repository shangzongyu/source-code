import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

ApplicationWindow {
    Button {
        style: ButtonStyle {
            label: Text {
                text: "A button"; font.pointSize: 12
                color:  control.pressed ?  "blue" : "green"
            }

            background: Rectangle {
                implicitWidth: 100; implicitHeight: 25
                border.width: control.activeFocus ? 2 : 1
                border.color: "#888"; radius: 4
                gradient: Gradient {
                    GradientStop {
                        position: 0 ;
                        color: control.pressed ? "#ccc" : "#eee"
                    }
                    GradientStop {
                        position: 1 ;
                        color: control.pressed ? "#aaa" : "#ccc"
                    }
                }
            }
        }
    }
}
