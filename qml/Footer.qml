import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    RowLayout {
        anchors.fill: parent

        Button {
            id: buttonNewGame

            text: "New game"
            Layout.preferredHeight: 1
            Layout.fillHeight: true
            Layout.fillWidth: true

            onClicked: {
                gameController.resetGame()
            }
        }

        Button {
            id: buttonNextRound

            text: "Next round"
            Layout.preferredHeight: 1
            Layout.fillHeight: true
            Layout.fillWidth: true

            enabled: gameController.roundOver && !gameController.gameOver
            onClicked: {
                gameController.nextRound()
            }
        }

        Button {
            id: buttonInfo

            text: "Info"
            Layout.preferredHeight: 1
            Layout.fillHeight: true
            Layout.fillWidth: true

            onClicked: {
                window.showExtraInfo = !window.showExtraInfo
            }
        }

        Button {
            id: buttonOk

            text: "Ok"
            Layout.preferredHeight: 1
            Layout.fillHeight: true
            Layout.fillWidth: true

            onClicked: {
            }
        }
    }
}
