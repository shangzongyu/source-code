import QtQuick 2.2

Row {
    Text {
        // 点标记
        font.pixelSize: 12; font.bold: true
        text: "text1"
    }
    Text {
        // 组标记
        font { pixelSize: 12; bold: true }
        text: "text2"
    }
}

