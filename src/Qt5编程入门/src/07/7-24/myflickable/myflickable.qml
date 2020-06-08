import QtQuick 2.2

Rectangle {
    width: 300; height: 300

    Flickable {
        id: flickable
        width: 300; height: 300
        contentWidth: image.width; contentHeight: image.height
        clip: true

        Image { id: image; source: "bigImage.jpg" }
    }

    Rectangle {
        id: scrollbar
        anchors.right: flickable.right
        y: flickable.visibleArea.yPosition * flickable.height
        width: 10
        height: flickable.visibleArea.heightRatio * flickable.height
        color: "black"
    }
}


