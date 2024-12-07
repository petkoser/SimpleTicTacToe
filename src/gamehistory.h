#ifndef GAMEHISTORY_H
#define GAMEHISTORY_H
#include <QString>
#include <QVector>
#include <QSettings>
#include <QDebug>

struct GameResult {
    QString player1;
    QString player2;
    QString winner;
};

class GameHistory
{
public:
    GameHistory();
    void loadSettings();
    void saveSettings();
    void add(QString player1, QString player2, QString winner);
    std::pair<int,int> getGameScore(QString player1, QString player2);

private:
    QVector<GameResult> history_;
    QSettings settings_;
};

#endif // GAMEHISTORY_H
