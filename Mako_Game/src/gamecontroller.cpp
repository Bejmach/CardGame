#include "gamecontroller.h"
#include <QDebug>

GameController::GameController(QObject *parent) : QObject(parent)
{
    m_gameMaster = new GameMaster(GameModes::Makao);
}

// GameController::~GameController()
// {
//     delete m_gameMaster;
//     for (auto bot : m_bots) {
//         delete bot;
//     }
// }

void GameController::initializeGame(int playerCount, int aiCount) {
    try {
        if (playerCount <= 0 || aiCount < 0) {
            throw std::invalid_argument("Invalid player counts");
        }

        m_player = new ClientPlayer();
        m_gameMaster->AddPlayer(m_player);

        for (int i = 0; i < aiCount; ++i) {
            ClientBot* bot = new ClientBot();
            m_bots.push_back(bot);
            try {
                m_gameMaster->AddPlayer(bot);
            } catch (const std::exception& e) {
                delete bot;
                throw;
            }
        }

        m_gameMaster->PrepareGame();
        m_gameMaster->StartGame();
        emit gameStateUpdated();
    } catch (const std::exception& e) {
        if (m_player) delete m_player;
        for (auto bot : m_bots) delete bot;
        m_bots.clear();

        emit errorOccurred(QString("Game initialization failed: %1").arg(e.what()));
    }
}

void GameController::playerPlayCard(int cardIndex)
{
    if (m_player && m_gameMaster->GetStarted()) {
        try {
            m_player->PlayCard(cardIndex);
            emit gameStateUpdated();

            if (m_player->HandSize() == 0) {
                emit playerWon();
            }
        } catch (const std::exception& e) {
            emit errorOccurred(QString("Invalid move: %1").arg(e.what()));
        }
    }
}

void GameController::playerDrawCard()
{
    if (m_player && m_gameMaster->GetStarted()) {
        try {
            m_player->DrawCard();
            emit gameStateUpdated();
        } catch (const std::exception& e) {
            emit errorOccurred(QString("Cannot draw card: %1").arg(e.what()));
        }
    }
}
