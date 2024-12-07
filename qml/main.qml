import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtGraphicalEffects 1.15

ApplicationWindow {
    id: window

    property bool showExtraInfo: false
    property color colorBackground: "#A0AAC3"
    property color colorGrid: "#FAFAFA"
    property color colorGridAlt: "#E0E0E0"
    property color colorTextWarning: "#AA0000"
    property color colorTextDefault: "black"

    visible: true
    title: "TicTacToe"

    Rectangle {
        anchors.fill: parent
        color: colorBackground
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.centerIn: parent
        anchors.margins: 35
        spacing: 10

        CustomTextItem {
            Layout.preferredHeight: 1
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "TicTacToe"
            font.pixelSize: 96
        }

        CustomTextItem {
            Layout.preferredHeight: 1
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "Players: " + gameController.player1 + " VS " + gameController.player2
        }

        Item {
            Layout.preferredHeight: 1
            Layout.fillHeight: true
            Layout.fillWidth: true

            CustomText {
                id: labelPlayer1
                text: "Edit Player1: "
                font.pixelSize: 64
                anchors.centerIn: parent
            }

            TextEdit {
                text: gameController.player1
                font.pixelSize: 64
                anchors.left: labelPlayer1.right
                anchors.top: labelPlayer1.top
                color: gameController.player1 === gameController.player2 ? window.colorTextWarning : window.colorTextDefault

                onEditingFinished: {
                    if (text == "")
                        text = gameController.player1

                    gameController.player1 = text
                    gameController.resetGame()
                }
            }
        }

        Item {
            Layout.preferredHeight: 1
            Layout.fillHeight: true
            Layout.fillWidth: true

            CustomText {
                id: labelPlayer2
                text: "Edit Player2: "
                font.pixelSize: 64
                anchors.centerIn: parent
            }

            TextEdit {
                text: gameController.player2
                font.pixelSize: 64
                anchors.left: labelPlayer2.right
                anchors.top: labelPlayer2.top
                color: gameController.player1 === gameController.player2 ? "red" : "black"

                onEditingFinished: {
                    if (text == "")
                        text = gameController.player2

                    gameController.player2 = text
                    gameController.resetGame()
                }
            }
        }

        CustomTextItem {
            Layout.preferredHeight: 1
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "Round score: " + gameController.player1RoundScore + " VS " + gameController.player2RoundScore
        }

        CustomTextItem {
            Layout.preferredHeight: 1
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "Game score: " + gameController.player1GameScore + " VS " + gameController.player2GameScore
        }

        CustomTextItem {
            Layout.preferredHeight: 1
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "Round: " + (gameController.round + 1)
        }

        CustomTextItem {
            Layout.preferredHeight: 1
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "Turn: " + gameController.currentPlayer
        }

        RowLayout {
            Layout.preferredHeight: 10
            Layout.fillHeight: true
            Layout.fillWidth: true

            GameInfo {
                visible: window.showExtraInfo
                Layout.preferredWidth: visible ? 1 : 0
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            GameBoard {
                Layout.preferredWidth: 2
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }

        Item {
            Layout.preferredHeight: 1
            Layout.fillHeight: true
            Layout.fillWidth: true

            CustomText {
                anchors.centerIn: parent
                text: gameController.gameOver ?
                          "Player won game: " + gameController.gameWinner :
                          gameController.roundWinner ?
                              "Player won round: " + gameController.roundWinner :
                              "Draw"
                visible: gameController.roundOver || gameController.gameOver
                font.pixelSize: 64
            }
        }

        Footer {
            Layout.preferredHeight: 1
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }

}
