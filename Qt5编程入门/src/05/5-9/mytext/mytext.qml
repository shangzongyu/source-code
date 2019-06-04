import QtQuick 2.2

Row {
    Text {
        font.pointSize: 24; text: "Normal"
    }
    Text {
        font.pointSize: 24; text: "Raised"
        style: Text.Raised
        styleColor: "#AAAAAA"
    }
    Text {
        font.pointSize: 24; text: "Outline"
        style: Text.Outline
        styleColor: "red"
    }
    Text {
        font.pointSize: 24; text: "Sunken"
        style: Text.Sunken
        styleColor: "#AAAAAA"
    }
}

