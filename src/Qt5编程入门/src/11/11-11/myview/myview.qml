import QtQuick 2.2

Rectangle {
    width: 240; height: 300

    ListView {
        id: listView; anchors.fill: parent; anchors.margins: 20
        clip: true; model: 100; delegate: numberDelegate
        spacing: 5; highlight: highlight
        focus: true; highlightFollowsCurrentItem: false
        preferredHighlightBegin: 100; preferredHighlightEnd:150
        highlightRangeMode :ListView.ApplyRange
    }

    Component {
        id: highlight
        Rectangle {
            width: 180; height: 40
            color: "lightsteelblue"; radius: 5
            y: listView.currentItem.y
            Behavior on y {
                SpringAnimation { spring: 3; damping: 0.2 }
            }
        }
    }

    Component {
        id: numberDelegate
        Item {
            width: 40; height: 40
            Text {
                anchors.centerIn: parent
                font.pixelSize: 10; text: index
            }
        }
    }
}



