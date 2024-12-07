#include "gamecontroller.h"

GameController::GameController(QObject *parent)
    : QObject(parent), board_(QVector<QVector<QString>>(3, QVector<QString>(3, ""))), settings_("settings.ini", QSettings::Format::IniFormat)
{
    loadSettings();
    saveSettings();

    gameHistory_.loadSettings();
    gameHistory_.saveSettings();

    updateGameScore();
}

QVector<QVector<QString>> GameController::getBoard() const
{
    return board_;
}

QString GameController::getCurrentPlayer() const
{
    return currentPlayer_;
}

QString GameController::getPlayer1() const
{
    return player1_;
}

QString GameController::getPlayer2() const
{
    return player2_;
}

QString GameController::getGameWinner() const
{
    return gameWinner_;
}

QString GameController::getRoundWinner() const
{
    return roundWinner_;
}

bool GameController::getGameOver() const
{
    return gameOver_;
}

bool GameController::getRoundOver() const
{
    return roundOver_;
}

quint32 GameController::getRound() const
{
    return round_;
}

quint32 GameController::getPlayer1RoundScore() const
{
    return player1RoundScore_;
}

quint32 GameController::getPlayer2RoundScore() const
{
    return player2RoundScore_;
}

quint32 GameController::getPlayer1GameScore() const
{
    return player1GameScore_;
}

quint32 GameController::getPlayer2GameScore() const
{
    return player2GameScore_;
}

void GameController::setPlayer1(QString player1)
{
    player1_ = player1;
    emit signalPlayer1Changed();

    saveSettings();
    updateGameScore();
}

void GameController::setPlayer2(QString player2)
{
    player2_ = player2;
    emit signalPlayer2Changed();

    saveSettings();
    updateGameScore();
}

void GameController::setRoundOver(bool roundOver)
{
    roundOver_ = roundOver;
    emit signalRoundOverChanged();
}

void GameController::setGameOver(bool gameOver)
{
    gameOver_ = gameOver;
    emit signalGameOverChanged();
}

void GameController::setRoundWinner(QString roundWinner)
{
    roundWinner_ = roundWinner;
    emit signalRoundWinnerChanged();
    setRoundOver();

    if (roundWinner == player1_) {
        player1RoundScore_++;
        emit signalPlayer1RoundScoreChanged();
    }
    else if (roundWinner == player2_) {
        player2RoundScore_++;
        emit signalPlayer2RoundScoreChanged();
    }
    else {
        return;
    }

    if (player1RoundScore_ >= 2 || player2RoundScore_ >= 2) {
        setGameWinner(roundWinner);
        setGameOver();
    }
}

void GameController::setGameWinner(QString gameWinner)
{
    gameWinner_ = gameWinner;
    emit signalGameWinnerChanged();

    gameHistory_.add(player1_, player2_, gameWinner_);
    updateGameScore();
    gameHistory_.saveSettings();
}

void GameController::makeMove(int row, int col)
{
    if (roundOver_)
        return;

    if (gameOver_)
        return;

    if (board_[row][col].isEmpty()) {
        board_[row][col] = currentPlayer_;
        checkRoundWinner();

        currentPlayer_ = (currentPlayer_ == player1_ ? player2_ : player1_);
        emit signalBoardChanged();
        emit signalCurrentPlayerChanged();
    }
}

void GameController::resetGame()
{
    board_ = QVector<QVector<QString>>(3, QVector<QString>(3, ""));
    currentPlayer_ = getRandomPlayer();
    gameWinner_ = "";
    roundWinner_ = "";
    gameOver_ = false;
    roundOver_ = false;
    round_ = 0;
    player1RoundScore_ = 0;
    player2RoundScore_ = 0;

    emit signalBoardChanged();
    emit signalCurrentPlayerChanged();
    emit signalGameWinnerChanged();
    emit signalRoundWinnerChanged();
    emit signalGameOverChanged();
    emit signalRoundOverChanged();
    emit signalRoundChanged();
    emit signalPlayer1RoundScoreChanged();
    emit signalPlayer2RoundScoreChanged();
    emit signalPlayer1GameScoreChanged();
    emit signalPlayer2GameScoreChanged();
    emit signalPlayer1Changed();
    emit signalPlayer2Changed();
}

void GameController::nextRound()
{
    board_ = QVector<QVector<QString>>(3, QVector<QString>(3, ""));
    currentPlayer_ = getRandomPlayer();
    roundOver_ = false;
    roundWinner_ = "";
    round_++;

    emit signalBoardChanged();
    emit signalCurrentPlayerChanged();
    emit signalRoundOverChanged();
    emit signalRoundWinnerChanged();
    emit signalRoundChanged();
}

QString GameController::getRandomPlayer() const
{
    return (QRandomGenerator64::global()->generate() % 2) ? player1_ : player2_;
}

void GameController::checkRoundWinner()
{
    // verticals horizontals
    for (int i = 0; i < 3; ++i) {
        if (!board_[i][0].isEmpty() && board_[i][0] == board_[i][1] && board_[i][0] == board_[i][2]) {
            setRoundWinner(currentPlayer_);
            return;
        }
        if (!board_[0][i].isEmpty() && board_[0][i] == board_[1][i] && board_[0][i] == board_[2][i]) {
            setRoundWinner(currentPlayer_);
            return;
        }
    }

    // diagonals
    if (!board_[0][0].isEmpty() && board_[0][0] == board_[1][1] && board_[0][0] == board_[2][2]) {
        setRoundWinner(currentPlayer_);
        return;
    }
    if (!board_[0][2].isEmpty() && board_[0][2] == board_[1][1] && board_[0][2] == board_[2][0]) {
        setRoundWinner(currentPlayer_);
        return;
    }

    // full board
    if (std::all_of(board_.begin(), board_.end(), [](const QVector<QString>& row) {
            return std::all_of(row.begin(), row.end(), [](const QString& cell) {
                return !cell.isEmpty();
            });
        })) {
        setRoundWinner("");
    }
}

void GameController::loadSettings()
{
    settings_.beginGroup("Common");
    player1_ = settings_.value("player1", player1_).toString();
    player2_ = settings_.value("player2", player2_).toString();
    settings_.endGroup();
}

void GameController::saveSettings()
{
    settings_.beginGroup("Common");
    settings_.setValue("player1", player1_);
    settings_.setValue("player2", player2_);
    settings_.endGroup();
}

void GameController::updateGameScore()
{
    auto [player1GameScore, player2GameScore] = gameHistory_.getGameScore(player1_, player2_);
    player1GameScore_ = player1GameScore;
    player2GameScore_ = player2GameScore;

    emit signalPlayer1GameScoreChanged();
    emit signalPlayer2GameScoreChanged();
}
