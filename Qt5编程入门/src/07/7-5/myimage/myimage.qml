import QtQuick 2.2

Image {
    id: image
    width: 200; height: 200
    fillMode: Image.Tile
    source: "http://www.baidu.com/img/baidu_sylogo1.gif"
    sourceSize.width: 100; sourceSize.height: 100;

    onStatusChanged: {
        if (image.status == Image.Ready) console.log('Loaded')
        else if (image.status == Image.Loading) console.log('Loading')
    }
}
