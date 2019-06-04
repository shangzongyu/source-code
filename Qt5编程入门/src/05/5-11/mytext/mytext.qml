import QtQuick 2.2

Item {
    width: 400
    height: 100
    Text {
        textFormat: Text.RichText; font.pointSize: 24
        text: "欢迎访问<a href=\"http://qter.org\">Qter开源社区</a>"
        onLinkActivated: console.log(link + " link activated");
    }
}

