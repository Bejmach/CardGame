#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "GameMaster.h"
#include "src/ClientBot.h"
#include "src/ClientPlayer.h"
#include <QObject>

class GameController : public QObject
{
    Q_OBJECT
public:
    explicit GameController(QObject *parent = nullptr);
    ~GameController() {
        delete m_gameMaster;
        for (auto bot : m_bots) {
            delete bot;
        }
        m_bots.clear();
    }
    void initializeGame(int playerCount, int aiCount);
    void playerPlayCard(int cardIndex);
    void playerDrawCard();

    GameMaster* getGameMaster() const { return m_gameMaster; }

    //update UI
signals:
    void gameStateUpdated();
    void playerWon();
    void errorOccurred(const QString& message);

private:
    GameMaster* m_gameMaster;
    ClientPlayer* m_player;
    std::vector<ClientBot*> m_bots;
};

#endif // GAMECONTROLLER_H
