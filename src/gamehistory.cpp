#include "gamehistory.h"

GameHistory::GameHistory() : settings_("history.ini", QSettings::Format::IniFormat){}

void GameHistory::loadSettings()
{
    history_.clear();
    int size = settings_.beginReadArray("History");
    for (int i = 0; i < size; ++i) {
        settings_.setArrayIndex(i);
        auto player1 = settings_.value("player1").toString();
        auto player2 = settings_.value("player2").toString();
        auto winner = settings_.value("winner").toString();
        history_.push_back(GameResult {player1, player2, winner});
        //qWarning().noquote() << QString("[GameHistory] loadSettings: game #%1, '%2' vs '%3' winner %4").arg(i).arg(player1).arg(player2).arg(winner);
    }
    settings_.endArray();
}

void GameHistory::saveSettings()
{
    settings_.beginWriteArray("History");
    for (int i = 0; i < history_.size(); ++i) {
        settings_.setArrayIndex(i);
        settings_.setValue("player1", history_[i].player1);
        settings_.setValue("player2", history_[i].player2);
        settings_.setValue("winner", history_[i].winner);
    }
    settings_.endArray();
    //qWarning().noquote() << QString("[GameHistory] saveSettings: games count - %1").arg(history_.count());
}

void GameHistory::add(QString player1, QString player2, QString winner)
{
    history_.push_back(GameResult {player1, player2, winner});
}

std::pair<int,int> GameHistory::getGameScore(QString player1, QString player2)
{
    int player1GameScore = 0, player2GameScore = 0;
    for (auto itr = history_.begin(); itr != history_.end(); itr++)
    {
        if ((player1 == itr->player1 && player2 == itr->player2) || (player1 == itr->player2 && player2 == itr->player1)) {
            if (player1 == itr->winner)
                player1GameScore++;
            else if (player2 == itr->winner)
                player2GameScore++;
        }
    }

    //qWarning().noquote() << QString("[GameHistory] getGameScore: player1GameScore_ - %1, player2GameScore_ - %2").arg(player1GameScore).arg(player2GameScore);
    return {player1GameScore, player2GameScore};
}
