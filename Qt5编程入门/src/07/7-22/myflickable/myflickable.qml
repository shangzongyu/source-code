import QtQuick 2.2

Flickable {
    width: 200; height: 200
contentWidth: image.width; contentHeight: image.height

    Image { id: image; source: "bigImage.jpg" }
}

