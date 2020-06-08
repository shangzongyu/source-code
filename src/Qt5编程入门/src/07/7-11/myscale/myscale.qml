import QtQuick 2.2

Item {
    width: 250; height: 150
    Image {
        x:20; y:10; source: "qtlogo.png"
        transform: Scale { origin.x: 25; origin.y: 25; xScale: 2}
    }
}


