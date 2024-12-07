import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15
import QtMultimedia 5.15

Grid {
    id: gameGrid

    property color colorCross: "red"
    property color colorRound: "green"
    property int cellWidth: width / 3

    columns: 3
    rows: 3
    spacing: 5

    enabled: gameController.player1 !== gameController.player2 && !gameController.roundOver && !gameController.gameOver
    opacity: enabled ? 1.0 : 0.2

    SoundEffect {
        id: crossSound
        source: "qrc:/sounds/cross.wav"
    }

    SoundEffect {
        id: roundSound
        source: "qrc:/sounds/round.wav"
    }

    SoundEffect {
        id: fatalitySound
        source: "qrc:/sounds/fatality.wav"
    }

    SoundEffect {
        id: fightSound
        source: "qrc:/sounds/fight.wav"
    }

    SoundEffect {
        id: round1Sound
        source: "qrc:/sounds/round1.wav"
        onPlayingChanged: if (playing === false) fightSound.play()
    }

    SoundEffect {
        id: round2Sound
        source: "qrc:/sounds/round2.wav"
        onPlayingChanged: if (playing === false) fightSound.play()
    }

    SoundEffect {
        id: round3Sound
        source: "qrc:/sounds/round3.wav"
        onPlayingChanged: if (playing === false) fightSound.play()
    }

    Connections {
        target: gameController

        function onSignalGameOverChanged() {
            if (gameController.gameOver)
                fatalitySound.play()
        }

        function onSignalRoundChanged() {
            if (gameController.round === 0)
                round1Sound.play();
            else if (gameController.round === 1)
                round2Sound.play();
            else if (gameController.round === 2)
                round3Sound.play();
            else
                fightSound.play();
        }
    }

    Repeater {
        model: 9
        delegate: Rectangle {
            width: gameGrid.cellWidth
            height: width
            radius: 25
            color: index % 2 == 0 ? window.colorGrid : window.colorGridAlt

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (gameController.roundOver || gameController.gameOver)
                        return;

                    if (gameController.board[Math.floor(index / 3)][index % 3] === "")
                    {
                        if (gameController.currentPlayer === gameController.player1)
                            crossSound.play()
                        else
                            roundSound.play()
                    }

                    gameController.makeMove(Math.floor(index / 3), index % 3)
                }

                Item {
                    anchors.centerIn: parent
                    width: parent.width * 0.6
                    height: parent.height * 0.6

                    Image {
                        id: imageCross

                        visible: gameController.board[Math.floor(index / 3)][index % 3] === gameController.player1
                        source: "qrc:/images/cross.svg"
                        width: parent.width
                        height: parent.height
                    }

                    Glow {
                        source: imageCross
                        anchors.fill: imageCross
                        visible: imageCross.visible

                        radius: 8
                        samples: 17
                        color: gameGrid.colorCross
                    }

                    Image {
                        id: imageRound

                        visible: gameController.board[Math.floor(index / 3)][index % 3] === gameController.player2
                        source: "qrc:/images/round.svg"
                        width: parent.width
                        height: parent.height
                    }

                    Glow {
                        source: imageRound
                        anchors.fill: imageRound
                        visible: imageRound.visible

                        radius: 8
                        samples: 17
                        color: gameGrid.colorRound
                    }

                }
            }
        }
    }
}
