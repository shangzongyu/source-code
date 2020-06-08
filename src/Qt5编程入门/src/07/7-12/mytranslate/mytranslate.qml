import QtQuick 2.2

Item {
    width: 250; height: 150

    Image { source: "qtlogo.png" }

    Image {
        source: "qtlogo.png"
        transform: Translate { x:120; y: 50 }
    }
}

