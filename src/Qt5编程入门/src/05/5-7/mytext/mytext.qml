import QtQuick 2.2

Column {
    spacing: 20

    Text {
        width: 200
        text: "使文本在单行中对于超出部分不要进行省略"
    }
    Text {
        width: 200
        elide: Text.ElideLeft
        text: "使文本在单行中对于超出部分从左边进行省略"
    }
    Text {
        width: 200
        elide: Text.ElideMiddle
        text: "使文本在单行中对于超出部分从中间进行省略"
    }
    Text {
        width: 200
        elide: Text.ElideRight
        text: "使文本在单行中对于超出部分从右边进行省略"
    }
    Text {
        width: 200
        height: 30
        wrapMode: Text.WordWrap
        elide: Text.ElideRight
        text: "对于可换行的多行文本，如果设置了高度，可以对超出部分从右边进行省略"
    }
    Text {
        width: 200
        maximumLineCount: 2
        wrapMode: Text.WordWrap
        elide: Text.ElideRight
        text: "对于可换行的多行文本，如果设置了最大行数，可以对超出部分从右边进行省略"
    }
}

