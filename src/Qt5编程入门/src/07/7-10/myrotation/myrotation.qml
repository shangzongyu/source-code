import QtQuick 2.2

Row {
    x: 10; y: 10
    spacing: 10

    Image { source: "qtlogo.png" }

    Image {
        source: "qtlogo.png"
        transform: Rotation { origin.x: 30; origin.y: 30;
            axis { x: 0; y: 1; z: 0 } angle: 72 }
    }
}


