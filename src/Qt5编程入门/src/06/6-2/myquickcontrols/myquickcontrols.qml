import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

ApplicationWindow {

    id: window; width: 800; height: 600;
    contentItem.minimumWidth:400; contentItem.minimumHeight:300;
    contentItem.maximumWidth:800; contentItem.maximumHeight:600;

    // 中心区域
    TextArea { id: myContent; anchors.fill: parent }

    Action {
        id: quitAction; text: qsTr("Quit")
        shortcut: "ctrl+q"; iconSource: "images/quit.png"
        onTriggered: Qt.quit()
    }
    Action {
        id: cutAction; text: qsTr("Cut")
        shortcut: "ctrl+x"; iconSource: "images/cut.png"
        onTriggered: myContent.cut()
    }
    Action {
        id: copyAction; text: qsTr("Copy")
        shortcut: "Ctrl+C"; iconSource: "images/copy.png"
        onTriggered: myContent.copy()
    }
    Action {
        id: pasteAction; text: qsTr("Paste")
        shortcut: "ctrl+v"; iconSource: "images/paste.png"
        onTriggered: myContent.paste()
    }
    // 菜单栏
    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem { action: quitAction }
        }
        Menu {
            title: qsTr("&Edit")
            MenuItem { action: cutAction }
            MenuItem { action: copyAction }
            MenuItem { action: pasteAction }
        }
    }
    // 工具栏
    toolBar: ToolBar {
        id: mainToolBar
        width: parent.width

        Row {
            anchors.fill: parent
            ToolButton { action: cutAction }
            ToolButton { action: copyAction }
            ToolButton { action: pasteAction }
        }
    }
    // 状态栏
    statusBar: StatusBar {
        RowLayout { Label { text: "Ready." } Label { text: "welcome." } }
    }
}
