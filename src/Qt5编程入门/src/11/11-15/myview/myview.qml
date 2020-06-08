import QtQuick 2.2

Rectangle {
    width: 360; height: 360

    PathView {
        anchors.fill: parent;
        delegate: delegate; model: 50; pathItemCount: 20
        preferredHighlightBegin: 0.5; preferredHighlightEnd: 0.5
        highlight: Component {
            Rectangle {
                width: 20; height: 20; color: "black"; radius: 5
                visible: PathView.onPath; opacity: 0.4
            }
        }

        path: Path {
            startX: 0; startY: 0
            PathAttribute { name: "itemScale"; value: 1.0 }
            PathAttribute { name: "itemOpacity"; value: 1.0 }

            PathLine { x: 120; y: 120}
            PathPercent { value:0.2 }
            PathAttribute { name: "itemScale"; value: 0.3 }
            PathAttribute { name: "itemOpacity"; value: 0.3 }

            PathLine { x: 240; y: 120 }
            PathPercent { value:0.6 }
            PathAttribute { name: "itemScale"; value: 0.7 }
            PathAttribute { name: "itemRadius"; value: 6 }

            PathQuad { x: 300; y: 330; controlX: 320; controlY: 180 }
        }

        focus: true

        Keys.onLeftPressed: decrementCurrentIndex()
        Keys.onRightPressed: incrementCurrentIndex()
    }

    Component {
        id: delegate
        Item {
            id: wrapper; width: 16; height: 16
            scale: PathView.itemScale; opacity: PathView.itemOpacity
            Rectangle {
                anchors.fill: parent
                color: wrapper.PathView.isCurrentItem ? "red" : "black"
                radius: wrapper.PathView.itemRadius
            }
        }
    }
}
