import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Window 2.1

ApplicationWindow {
    width: 300; height: 200

    TabView {
        anchors.fill: parent

        Tab { title: "Home" }
        Tab { title: "Edit" }
        Tab { title: "View" }
        Tab { title: "Help" }
    }
}

