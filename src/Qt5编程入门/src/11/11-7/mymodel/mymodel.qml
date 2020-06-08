import QtQuick 2.2
import QtQuick.XmlListModel 2.0

Rectangle {
    width: 500; height: 340

    XmlListModel {
        id: xmlModel
        source: "http://news.163.com/special/00011K6L/rss_newstop.xml"
        query: "/rss/channel/item"

        XmlRole { name: "title"; query: "title/string()" }
        XmlRole { name: "pubDate"; query: "pubDate/string()" }
    }

    ListView {
        width: 180; height: 300
        model: xmlModel
        delegate: Text { text: title + ": " + pubDate }
    }
}


