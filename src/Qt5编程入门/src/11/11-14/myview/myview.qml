import QtQuick 2.2

ListView {
    width: 240; height: 320
    model: ListModel {}

    delegate: Rectangle {
        width: 100; height: 30; border.width: 1
        color: "lightsteelblue"
        Text { anchors.centerIn: parent; text: name }
    }
    add: Transition {
        NumberAnimation { property: "opacity";
            from: 0; to: 1.0; duration: 400 }
        NumberAnimation { property: "scale";
            from: 0; to: 1.0; duration: 400 }
    }
    //    displaced: Transition {
    //        NumberAnimation { properties: "x,y"; duration: 400;
    //               easing.type: Easing.OutBounce }
    //    }

    // 基于索引的延迟动画
    //    displaced: Transition {
    //        id: dispTrans
    //        SequentialAnimation {
    //            PauseAnimation {
    //                duration: (dispTrans.ViewTransition.index -
    //                           dispTrans.ViewTransition.targetIndexes[0]) * 100
    //            }
    //            NumberAnimation { properties: "x,y"; duration: 400; easing.type: Easing.OutBounce }
    //        }
    //    }

    //
    // 移动到中间的动画效果
    //    displaced: Transition {
    //        id: dispTrans
    //        SequentialAnimation {
    //            PauseAnimation {
    //                duration: (dispTrans.ViewTransition.index -
    //                           dispTrans.ViewTransition.targetIndexes[0]) * 100
    //            }
    //            ParallelAnimation {
    //                NumberAnimation {
    //                    property: "x"; to: dispTrans.ViewTransition.item.x + 20
    //                    easing.type: Easing.OutQuad
    //                }
    //                NumberAnimation {
    //                    property: "y"; to: dispTrans.ViewTransition.item.y + 50
    //                    easing.type: Easing.OutQuad
    //                }
    //            }
    //            NumberAnimation { properties: "x,y"; duration: 500; easing.type: Easing.OutBounce }
    //        }
    //    }

    // 解决快速添加问题
    displaced: Transition {
        NumberAnimation { properties: "x,y"; duration: 400; easing.type: Easing.OutBounce }

        // 确保opacity和scale值变为1.0
        NumberAnimation { property: "opacity"; to: 1.0 }
        NumberAnimation { property: "scale"; to: 1.0 }
    }



    focus: true
    Keys.onSpacePressed: model.insert(0, { "name": "Item " + model.count })
}





