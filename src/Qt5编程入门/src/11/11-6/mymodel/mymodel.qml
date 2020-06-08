import QtQuick 2.2
import QtQml.Models 2.1

Rectangle {
    width: 200; height: 400

    DelegateModel {
        id: delegateModel
        delegate: Package {
            Text { id: listDelegate; width: parent.width; height: 25;
                text: 'in list'; Package.name: 'list'}
            Text { id: gridDelegate; width: parent.width / 2; height: 50;
                text: 'in grid'; Package.name: 'grid' }
        }

        model: 5
    }

    ListView {
        height: parent.height/2; width: parent.width
        model: delegateModel.parts.list
    }
    GridView {
        y: parent.height/2;
        height: parent.height/2; width: parent.width;
        cellWidth: width / 2; cellHeight: 50
        model: delegateModel.parts.grid
    }
}

