import QtQuick 2.2

//BorderImage {
//    width: 180; height: 180
//    border { left: 30; top: 30; right: 30; bottom: 30 }
//    horizontalTileMode: BorderImage.Stretch
//    verticalTileMode: BorderImage.Stret
//    source: "colors.png"
//}


BorderImage {
    width: 180; height: 180
    border { left: 30; top: 30; right: 30; bottom: 30 }
    horizontalTileMode: BorderImage.Repeat
    verticalTileMode: BorderImage.Repeat
    source: "colors.png"
}

