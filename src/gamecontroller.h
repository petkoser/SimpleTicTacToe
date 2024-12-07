#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QVector>
#include <QSettings>
#include <QString>
#include <QDebug>
#include <QRandomGenerator64>
#include "gamehistory.h"

class GameController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector<QVector<QString>> board READ getBoard NOTIFY signalBoardChanged)
    Q_PROPERTY(QString currentPlayer READ getCurrentPlayer NOTIFY signalCurrentPlayerChanged)
    Q_PROPERTY(QString player1 READ getPlayer1 WRITE setPlayer1 NOTIFY signalPlayer1Changed)
    Q_PROPERTY(QString player2 READ getPlayer2 WRITE setPlayer2 NOTIFY signalPlayer2Changed)
    Q_PROPERTY(QString gameWinner READ getGameWinner NOTIFY signalGameWinnerChanged)
    Q_PROPERTY(QString roundWinner READ getRoundWinner NOTIFY signalRoundWinnerChanged)
    Q_PROPERTY(bool gameOver READ getGameOver NOTIFY signalGameOverChanged)
    Q_PROPERTY(bool roundOver READ getRoundOver NOTIFY signalRoundOverChanged)
    Q_PROPERTY(quint32 round READ getRound NOTIFY signalRoundChanged)
    Q_PROPERTY(quint32 player1RoundScore READ getPlayer1RoundScore NOTIFY signalPlayer1RoundScoreChanged)
    Q_PROPERTY(quint32 player2RoundScore READ getPlayer2RoundScore NOTIFY signalPlayer2RoundScoreChanged)
    Q_PROPERTY(quint32 player1GameScore READ getPlayer1GameScore NOTIFY signalPlayer1GameScoreChanged)
    Q_PROPERTY(quint32 player2GameScore READ getPlayer2GameScore NOTIFY signalPlayer2GameScoreChanged)

public:
    explicit GameController(QObject *parent = nullptr);

    QVector<QVector<QString>> getBoard() const;
    QString getCurrentPlayer() const;
    QString getPlayer1() const;
    QString getPlayer2() const;
    QString getGameWinner() const;
    QString getRoundWinner() const;
    bool getGameOver() const;
    bool getRoundOver() const;
    quint32 getRound() const;
    quint32 getPlayer1RoundScore() const;
    quint32 getPlayer2RoundScore() const;
    quint32 getPlayer1GameScore() const;
    quint32 getPlayer2GameScore() const;

    void setPlayer1(QString player1);
    void setPlayer2(QString player2);
    void setRoundOver(bool roundOver = true);
    void setGameOver(bool gameOver = true);
    void setRoundWinner(QString roundWinner);
    void setGameWinner(QString gameWinner);

    Q_INVOKABLE void makeMove(int row, int col);
    Q_INVOKABLE void resetGame();
    Q_INVOKABLE void nextRound();

signals:
    void signalBoardChanged();
    void signalCurrentPlayerChanged();
    void signalGameWinnerChanged();
    void signalRoundWinnerChanged();
    void signalGameOverChanged();
    void signalRoundOverChanged();
    void signalRoundChanged();
    void signalPlayer1RoundScoreChanged();
    void signalPlayer2RoundScoreChanged();
    void signalPlayer1GameScoreChanged();
    void signalPlayer2GameScoreChanged();
    void signalPlayer1Changed();
    void signalPlayer2Changed();

private:
    QString getRandomPlayer() const;
    void checkRoundWinner();
    void loadSettings();
    void saveSettings();
    void updateGameScore();

    QString player1_ = "Superman";
    QString player2_ = "Batman";

    QVector<QVector<QString>> board_;
    QString currentPlayer_;
    QString gameWinner_;
    QString roundWinner_;
    bool gameOver_ = true;
    bool roundOver_ = true;
    quint32 round_ = 0;
    quint32 player1RoundScore_ = 0;
    quint32 player2RoundScore_ = 0;
    quint32 player1GameScore_ = 0;
    quint32 player2GameScore_ = 0;
    QSettings settings_;

    GameHistory gameHistory_;
};

#endif // GAMECONTROLLER_H
