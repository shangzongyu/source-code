import QtQuick 2.2
import QtMultimedia 5.0
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1

ApplicationWindow {
    id: window; width: 300; height: 300

    toolBar: ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton { text: qsTr("播放"); onClicked: audio.play() }
            ToolButton { text: qsTr("暂停"); onClicked: audio.pause() }
            ToolButton { text: qsTr("停止"); onClicked: audio.stop() }
        }
    }
    ColumnLayout {
        spacing: 10
        Text { text: qsTr("进度：") }
        Slider { maximumValue: audio.duration; value: audio.position;
            onValueChanged: audio.seek(value) }
        Text { text: qsTr("音量：") }
        Slider { maximumValue: 1.0; value: audio.volume;
            onValueChanged: audio.volume = value }
        Text { text: qsTr("循环次数：") }
        SpinBox { value: 1; onValueChanged: audio.loops = value }
        Text { text: qsTr("播放速度：") }
        SpinBox { value: 1.0; decimals: 1; stepSize: 0.1
            onValueChanged: audio.playbackRate = value }
    }
    Audio { id: audio; source: "music.mp3" }
}


