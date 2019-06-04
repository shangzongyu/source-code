import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Window 2.1

ApplicationWindow {
    ExclusiveGroup { id: radioInputGroup }

    toolBar: ToolBar {
        id: mainToolBar; width: parent.width

        Row {
            anchors.fill: parent
            ToolButton {
                id: dabRadioInput; text: "DAB";
                checkable: true; exclusiveGroup: radioInputGroup

            }
            ToolButton {
                id: fmRadioInput; text: "FM";
                checkable: true; exclusiveGroup: radioInputGroup
            }
            ToolButton {
                id: amRadioInput; text: "AM";
                checkable: true; exclusiveGroup: radioInputGroup
            }
        }
    }
}



