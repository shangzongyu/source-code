import QtQuick 2.2

Item {
    width: 150; height: 200

    ListModel {
        id:  listModel
    }

    Component {
        id: delegate
        Text { id: nameField; text: time}
    }

    ListView {
        anchors.fill: parent
        model: listModel; delegate: delegate
    }

    WorkerScript {
        id: worker; source: "dataloader.js"
    }

    Timer {
        interval: 2000; repeat: true
        running: true; triggeredOnStart: true

        onTriggered: {
            var msg = {'action': 'appendCurrentTime', 'model': listModel};
            worker.sendMessage(msg);
        }
    }
}

