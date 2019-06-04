import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.1
import QtMultimedia 5.0
import QtWinExtras 1.0 as Win

Window {
    id: window
    title: qsTr("My Quick Player")
    width: 300; height: 60

    minimumWidth: row.implicitWidth + 18
    minimumHeight: column.implicitHeight + 18

    MediaPlayer {
        id: mediaPlayer
        autoPlay: true
        readonly property string title:
            !!metaData.author && !!metaData.title
            ? qsTr("%1 - %2").arg(metaData.author).arg(metaData.title)
            : metaData.author || metaData.title || source
    }

    ColumnLayout {
        id: column

        anchors.margins: 9; anchors.fill: parent

        Label {
            id: infoLabel;

            elide: Qt.ElideLeft
            verticalAlignment: Qt.AlignVCenter
            text: mediaPlayer.errorString || mediaPlayer.title
            Layout.minimumHeight: infoLabel.implicitHeight
            Layout.fillWidth: true; Layout.fillHeight: true
        }

        RowLayout {
            id: row

            Button {
                id: openButton; text: qsTr("...")
                Layout.preferredWidth: openButton.implicitHeight
                onClicked: fileDialog.open()

                FileDialog {
                    id: fileDialog

                    title: qsTr("Open file")
                    nameFilters: [qsTr("MP3 files (*.mp3)"),
                        qsTr("All files (*.*)")]
                    onAccepted: mediaPlayer.source
                                = fileDialog.fileUrl
                }
            }

            Button {
                id: playButton

                enabled: mediaPlayer.hasAudio
                Layout.preferredWidth: playButton.implicitHeight
                iconSource: mediaPlayer.playbackState === MediaPlayer.PlayingState
                            ? "qrc:/images/pause-16.png" : "qrc:/images/play-16.png"
                onClicked: mediaPlayer.playbackState === MediaPlayer.PlayingState
                           ? mediaPlayer.pause() : mediaPlayer.play()
            }

            Slider {
                id: positionSlider

                Layout.fillWidth: true
                maximumValue: mediaPlayer.duration

                property bool sync: false

                onValueChanged: {
                    if (!sync)
                        mediaPlayer.seek(value)
                }

                Connections {
                    target: mediaPlayer
                    onPositionChanged: {
                        positionSlider.sync = true
                        positionSlider.value = mediaPlayer.position
                        positionSlider.sync = false
                    }
                }
            }

            Label {
                id: positionLabel

                readonly property int minutes:
                    Math.floor(mediaPlayer.position / 60000)
                readonly property int seconds:
                    Math.round((mediaPlayer.position % 60000) / 1000)

                text: Qt.formatTime(new Date(0, 0, 0, 0, minutes, seconds),
                                    qsTr("mm:ss"))
            }
        }
    }

    Win.DwmFeatures {
        id: dwm
        topGlassMargin: -1; leftGlassMargin: -1
        rightGlassMargin: -1; bottomGlassMargin: -1
    }

    Win.TaskbarButton {
        id: taskbar

        progress.value: mediaPlayer.position
        progress.maximum: mediaPlayer.duration
        progress.visible: mediaPlayer.hasAudio
        progress.paused: mediaPlayer.playbackState
                         === MediaPlayer.PausedState

        overlay.iconSource: mediaPlayer.playbackState
                            === MediaPlayer.PlayingState
                            ? "qrc:/images/play-32.png" :
                              mediaPlayer.playbackState
                              === MediaPlayer.PausedState ?
                                  "qrc:/images/pause-32.png"
                                : "qrc:/images/stop-32.png"
    }


    Win.ThumbnailToolBar {
        id: thumbbar

        Win.ThumbnailToolButton {
            tooltip: qsTr("Rewind")
            iconSource: "qrc:/images/backward-32.png"

            enabled: mediaPlayer.position > 0
            onClicked: mediaPlayer.seek(mediaPlayer.position
                                        - mediaPlayer.duration / 10)
        }

        Win.ThumbnailToolButton {
            tooltip: mediaPlayer.playbackState
                     === MediaPlayer.PlayingState
                     ? qsTr("Pause") : qsTr("Play")
            iconSource: mediaPlayer.playbackState
                        === MediaPlayer.PlayingState
                        ? "qrc:/images/pause-32.png" : "qrc:/images/play-32.png"

            enabled: mediaPlayer.hasAudio
            onClicked: mediaPlayer.playbackState
                       === MediaPlayer.PlayingState
                       ? mediaPlayer.pause() : mediaPlayer.play()
        }

        Win.ThumbnailToolButton {
            tooltip: qsTr("Fast forward")
            iconSource: "qrc:/images/forward-32.png"

            enabled: mediaPlayer.position < mediaPlayer.duration
            onClicked: mediaPlayer.seek(mediaPlayer.position
                                        + mediaPlayer.duration / 10)
        }
    }
}













