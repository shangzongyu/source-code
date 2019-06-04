import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Window 2.1

ApplicationWindow {
    ExclusiveGroup {
        id: radioInputGroup

        Action { id: dabRadioInput; text: "DAB"; checkable: true }
        Action { id: fmRadioInput; text: "FM"; checkable: true }
        Action { id: amRadioInput; text: "AM"; checkable: true }
    }

    toolBar: ToolBar {
        id: mainToolBar; width: parent.width

        Row {
            anchors.fill: parent
            ToolButton { action: dabRadioInput}
            ToolButton { action: fmRadioInput }
            ToolButton { action: amRadioInput }
        }
    }
}



