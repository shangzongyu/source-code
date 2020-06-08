import QtQuick 2.2
import QtMultimedia 5.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

ApplicationWindow {
    id: window; width: 300; height: 300

    toolBar: ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: qsTr("音频")
                onClicked: {
                    mediaplayer.source = "music.mp3"
                    mediaplayer.play()
                }
            }
            ToolButton {
                text: qsTr("视频")
                onClicked: {
                    mediaplayer.source = "video.wmv"
                    mediaplayer.play()
                }
            }
        }
    }
    MediaPlayer { id: mediaplayer }
    VideoOutput { anchors.fill: parent; source: mediaplayer }
}

