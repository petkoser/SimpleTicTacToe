import QtQuick 2.15

Column {
    CustomText {
        text: "currentPlayer: " + gameController.currentPlayer
    }

    CustomText {
        text: "player1: " + gameController.player1
    }

    CustomText {
        text: "player2: " + gameController.player2
    }

    CustomText {
        text: "gameWinner: " + gameController.gameWinner
    }

    CustomText {
        text: "roundWinner: " + gameController.roundWinner
    }

    CustomText {
        text: "round: " + gameController.round
    }

    CustomText {
        text: "player1RoundScore: " + gameController.player1RoundScore
    }

    CustomText {
        text: "player2RoundScore: " + gameController.player2RoundScore
    }
}

