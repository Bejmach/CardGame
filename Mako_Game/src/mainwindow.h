#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>
#include <QGridLayout>

//Backend includes
#include "GameMaster.h"
#include "ClientPlayer.h"
#include "ClientBot.h"
#include "Card.h"
#include "CardTranslator.h"

#include "gamecontroller.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override {
        if (gameTimer && gameTimer->isActive()) {
            gameTimer->stop();
        }
        delete gameTimer;
        delete m_gameController;
    }


private slots:
    void showGamePrepScreen();
    void startGame();
    void updateTimer();
    void handlePlayerWin();
    void handleGameError(const QString& errorMessage);

private:

    GameController* m_gameController;

    QStackedWidget *stackedWidget;

    //Start
    QWidget *startScreen;
    QPushButton *playButton;
    QPushButton *settingsButton;
    QPushButton *exitButton;

    //Game prep
    QWidget *gamePrepScreen;
    QComboBox *aiOpponentsCombo;
    QPushButton *gamePrepPlayButton;

    //Game
    QWidget *gameScreen;
    QGridLayout *gameGridLayout;
    QLabel *timerLabel;
    QLabel *stopwatchLabel;
    QTimer *gameTimer;
    int elapsedSeconds;
    QPushButton *playCardButton;
    QPushButton *passTakeButton;
    QVBoxLayout *aiOpponentsLayout;

    //AI/opponent containers
    QWidget *leftAiContainer;
    QWidget *topAiContainer;
    QWidget *rightAiContainer;

    void createStartScreen();
    void createGamePrepScreen();
    void createGameScreen();
    void updateClockDisplay();
    void updateStopwatchDisplay();

    //card display management
    QMap<QString, QPixmap> cardImages;
    QPixmap cardBackImage;

    GameMaster* gameMaster;
    int selectedCardIndex;

    void loadCardAssets();
    QLabel* createCardLabel(const Card* card, bool faceUp = true);
    void updateCardDisplay();

    //ui el
    QWidget* playerHandContainer;
    QHBoxLayout* playerHandLayout;
    QLabel* playedCardLabel;

    //Game actions
    void handlePlayCard();
    void handlePassTake();
    void updateGameState();
    void updateAiOpponents();
    void clearLayout(QLayout* layout);

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

};

#endif // MAINWINDOW_H
