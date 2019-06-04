import QtQuick 2.2

Item {
    id: container
    width: 500; height: 100

    Component.onCompleted: {
        var component = Qt.createComponent("SelfDestroyingRect.qml");
        for (var i=0; i<5; i++) {
            var object = component.createObject(container);
            object.x = (object.width + 10) * i;
        }
    }
}


