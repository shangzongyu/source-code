import QtQuick 2.2

Item {
    width: 100; height: 100

    Component {
        id: redSquare

        Rectangle {
            color: "red"; width: 10; height: 10
        }
    }

    Loader { sourceComponent: redSquare }
    Loader { sourceComponent: redSquare; x: 20 }
}


