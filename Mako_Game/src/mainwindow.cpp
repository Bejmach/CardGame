#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <QPainter>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), elapsedSeconds(0)
{
    setWindowTitle("Mako");
    setFixedSize(800, 600);

    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    createStartScreen();
    createGamePrepScreen();
    createGameScreen();

    m_gameController = new GameController(this);
    connect(m_gameController, &GameController::gameStateUpdated,
            this, &MainWindow::updateGameState);
    connect(m_gameController, &GameController::playerWon,
            this, &MainWindow::handlePlayerWin);
    connect(m_gameController, &GameController::errorOccurred,
            this, &MainWindow::handleGameError);

    stackedWidget->addWidget(startScreen);
    stackedWidget->addWidget(gamePrepScreen);
    stackedWidget->addWidget(gameScreen);
}

void MainWindow::createStartScreen()
{
    startScreen = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(startScreen);

    QLabel *title = new QLabel("Mako", startScreen);
    title->setAlignment(Qt::AlignCenter);
    QFont titleFont = title->font();
    titleFont.setPointSize(32);
    title->setFont(titleFont);

    playButton = new QPushButton("PLAY", startScreen);
    settingsButton = new QPushButton("Settings", startScreen);
    exitButton = new QPushButton("Exit", startScreen);

    //buttons
    QString buttonStyle = "QPushButton { font-size: 20px; padding: 10px; }";
    playButton->setStyleSheet(buttonStyle);
    settingsButton->setStyleSheet(buttonStyle);
    exitButton->setStyleSheet(buttonStyle);

    layout->addStretch();
    layout->addWidget(title);
    layout->addSpacing(50);
    layout->addWidget(playButton);
    layout->addWidget(settingsButton);
    layout->addWidget(exitButton);
    layout->addStretch();

    connect(playButton, &QPushButton::clicked, this, &MainWindow::showGamePrepScreen);
    connect(exitButton, &QPushButton::clicked, qApp, &QApplication::quit);
}

void MainWindow::createGamePrepScreen()
{
    gamePrepScreen = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(gamePrepScreen);

    QLabel *title = new QLabel("Select number of opponents", gamePrepScreen);
    title->setAlignment(Qt::AlignCenter);

    QLabel *aiLabel = new QLabel("Ai opponents:", gamePrepScreen);
    aiLabel->setAlignment(Qt::AlignCenter);

    aiOpponentsCombo = new QComboBox(gamePrepScreen);
    aiOpponentsCombo->addItems({"1", "2", "3"});
    aiOpponentsCombo->setFixedWidth(100);

    gamePrepPlayButton = new QPushButton("Play", gamePrepScreen);
    gamePrepPlayButton->setFixedWidth(200);

    layout->addStretch();
    layout->addWidget(title);
    layout->addSpacing(20);
    layout->addWidget(aiLabel);
    layout->addWidget(aiOpponentsCombo, 0, Qt::AlignCenter);
    layout->addSpacing(20);
    layout->addWidget(gamePrepPlayButton, 0, Qt::AlignCenter);
    layout->addStretch();

    connect(gamePrepPlayButton, &QPushButton::clicked, this, &MainWindow::startGame);
}

void MainWindow::createGameScreen()
{
    //Load card assets
    loadCardAssets();

    gameScreen = new QWidget();
    gameGridLayout = new QGridLayout(gameScreen);
    gameGridLayout->setContentsMargins(20, 20, 20, 20);

    //timer
    QWidget *timerWidget = new QWidget(gameScreen);
    QVBoxLayout *timerLayout = new QVBoxLayout(timerWidget);
    timerLabel = new QLabel("TIME", timerWidget);
    stopwatchLabel = new QLabel("00:00", timerWidget);

    timerLayout->addWidget(timerLabel);
    timerLayout->addWidget(stopwatchLabel);
    timerLayout->setAlignment(Qt::AlignCenter);


    // Player's hand
    playerHandContainer = new QWidget(gameScreen);
    playerHandLayout = new QHBoxLayout(playerHandContainer);
    playerHandLayout->setAlignment(Qt::AlignCenter);

    //Played currently
    playedCardLabel = createCardLabel(nullptr); // Empty at start

    //AI/opponents hands
    leftAiContainer = new QWidget(gameScreen);
    topAiContainer = new QWidget(gameScreen);
    rightAiContainer = new QWidget(gameScreen);

    //action buttons
    QVBoxLayout *buttonLayout = new QVBoxLayout();
    playCardButton = new QPushButton("Play", gameScreen);
    passTakeButton = new QPushButton("Pass and take", gameScreen);

    //Layout
    gameGridLayout->addWidget(timerWidget, 0, 2, Qt::AlignRight);
    gameGridLayout->addWidget(topAiContainer, 0, 1, Qt::AlignCenter);
    gameGridLayout->addWidget(leftAiContainer, 1, 0, Qt::AlignCenter);
    gameGridLayout->addWidget(playedCardLabel, 1, 1, Qt::AlignCenter);
    gameGridLayout->addWidget(rightAiContainer, 1, 2, Qt::AlignCenter);
    gameGridLayout->addWidget(playerHandContainer, 2, 0, 1, 3);
    gameGridLayout->addLayout(buttonLayout, 2, 2, Qt::AlignRight);

    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &MainWindow::updateTimer);

    connect(playCardButton, &QPushButton::clicked, this, &MainWindow::handlePlayCard);
    connect(passTakeButton, &QPushButton::clicked, this, &MainWindow::handlePassTake);
}


void MainWindow::showGamePrepScreen()
{
    stackedWidget->setCurrentWidget(gamePrepScreen);
}


void MainWindow::startGame()
{
    //backend init
    gameMaster = new GameMaster();

    //Add player and AI
    int aiCount = aiOpponentsCombo->currentText().toInt();
    m_gameController->initializeGame(1, aiCount); // 1 human player

    gameMaster->PrepareGame();
    gameMaster->StartGame();

    elapsedSeconds = 0;
    selectedCardIndex = -1;
    updateGameState();
    gameTimer->start(1000);

    stackedWidget->setCurrentWidget(gameScreen);
}

void MainWindow::updateClockDisplay()
{
    int minutes = elapsedSeconds / 60;
    int seconds = elapsedSeconds % 60;
    stopwatchLabel->setText(QString("%1:%2")
                            .arg(minutes, 2, 10, QLatin1Char('0'))
                            .arg(seconds, 2, 10, QLatin1Char('0')));
}

void MainWindow::updateTimer()
{
    elapsedSeconds++;
    updateStopwatchDisplay();
}

void MainWindow::updateStopwatchDisplay()
{
    int minutes = elapsedSeconds / 60;
    int seconds = elapsedSeconds % 60;
    stopwatchLabel->setText(QString("%1:%2")
                                .arg(minutes, 2, 10, QLatin1Char('0'))
                                .arg(seconds, 2, 10, QLatin1Char('0')));
}

void MainWindow::loadCardAssets() {
    // Load card back image
    if (!cardBackImage.load(":/cards/back.png")) {
        qWarning() << "Failed to load card back image from:" << ":/cards/back.png";
        cardBackImage = QPixmap(120, 180);
        cardBackImage.fill(Qt::darkBlue);
    }

    QStringList suits = {"hearts", "diamonds", "clubs", "spades"};
    QStringList values = {"2", "3", "4", "5", "6", "7", "8", "9", "10",
                          "jack", "queen", "king", "ace"};

    for (const QString& suit : suits) {
        for (const QString& value : values) {
            QString cardName = value + "_of_" + suit;
            QString resourcePath = ":/cards/" + cardName + ".svg";

            if (!cardImages[cardName].load(resourcePath)) {
                qWarning() << "Failed to load:" << resourcePath << "| File exists:" << QFile::exists(resourcePath);
                QPixmap fallback(120, 180);
                fallback.fill(QColor(200, 50, 50));
                QPainter painter(&fallback);
                painter.drawText(fallback.rect(), Qt::AlignCenter, cardName);
                cardImages[cardName] = fallback;
            }
        }
    }
}

QLabel* MainWindow::createCardLabel(const Card* card, bool faceUp)
{
    QLabel* cardLabel = new QLabel(this);
    cardLabel->setFixedSize(120, 180);

    if (faceUp && card) {
        QString suit = translate::suit::EN(card->GetSuit()).c_str();
        QString value = translate::name::EN(card->GetName()).c_str();
        QString cardName = value.toLower() + "_of_" + suit.toLower();
        cardLabel->setPixmap(cardImages[cardName].scaled(cardLabel->size(),
                                                         Qt::KeepAspectRatio,
                                                         Qt::SmoothTransformation));
    } else {
        cardLabel->setPixmap(cardBackImage.scaled(cardLabel->size(),
                                                  Qt::KeepAspectRatio,
                                                  Qt::SmoothTransformation));
    }

    return cardLabel;
}

void MainWindow::updateGameState()
{
    QLayoutItem* child;
    while ((child = playerHandLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    std::vector<Card*> playerHand = gameMaster->GetClients()[0]->GetHand();
    for (size_t i = 0; i < playerHand.size(); i++) {
        QLabel* cardLabel = createCardLabel(playerHand[i]);
        cardLabel->setProperty("cardIndex", (int)i);
        cardLabel->installEventFilter(this);
        playerHandLayout->addWidget(cardLabel);
    }


    Deck* deck = m_gameController->getGameMaster()->GetDeck();
    if (deck) {
        Card* lastUsed = deck->GetLastUsed();
        playedCardLabel->clear();
        if (lastUsed) {
            QLabel* newCard = createCardLabel(lastUsed);
            gameGridLayout->replaceWidget(playedCardLabel, newCard);
            delete playedCardLabel;
            playedCardLabel = newCard;
        }
    }

    updateAiOpponents();
}

void MainWindow::updateAiOpponents()
{
    clearLayout(leftAiContainer->layout());
    clearLayout(topAiContainer->layout());
    clearLayout(rightAiContainer->layout());

    std::vector<ClientBase*> clients = gameMaster->GetClients();
    for (size_t i = 1; i < clients.size(); i++) {
        int cardCount = clients[i]->HandSize();
        QWidget* aiWidget = new QWidget();
        QHBoxLayout* aiLayout = new QHBoxLayout(aiWidget);

        QLabel* aiLabel = new QLabel(QString("AI %1").arg(i));
        aiLayout->addWidget(aiLabel);

        for (int j = 0; j < cardCount; j++) {
            QLabel* cardBack = createCardLabel(nullptr, false);
            cardBack->setFixedSize(60, 90);
            aiLayout->addWidget(cardBack);
        }

        switch (i) {
        case 1: leftAiContainer->layout()->addWidget(aiWidget); break;
        case 2: topAiContainer->layout()->addWidget(aiWidget); break;
        case 3: rightAiContainer->layout()->addWidget(aiWidget); break;
        }
    }
}

void MainWindow::clearLayout(QLayout* layout)
{
    if (!layout) return;

    QLayoutItem* item;
    while ((item = layout->takeAt(0))) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

bool MainWindow::eventFilter(QObject* watched, QEvent* event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        QLabel* cardLabel = qobject_cast<QLabel*>(watched);
        if (cardLabel && cardLabel->property("cardIndex").isValid()) {
            selectedCardIndex = cardLabel->property("cardIndex").toInt();
            cardLabel->setStyleSheet("border: 2px solid yellow;");
            return true;
        }
    }
    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::handlePlayCard()
{
    if (selectedCardIndex >= 0) {
        gameMaster->GetClients()[0]->PlayCard(selectedCardIndex);
        selectedCardIndex = -1;
        updateGameState();
    }
}

void MainWindow::handlePassTake()
{
    gameMaster->GetClients()[0]->DrawCard();
    updateGameState();
}

void MainWindow::handlePlayerWin()
{
    QWidget* victoryScreen = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(victoryScreen);

    QLabel* victoryLabel = new QLabel("You Won!", victoryScreen);
    victoryLabel->setAlignment(Qt::AlignCenter);
    QFont font = victoryLabel->font();
    font.setPointSize(32);
    victoryLabel->setFont(font);

    QPushButton* closeButton = new QPushButton("Close Game", victoryScreen);
    connect(closeButton, &QPushButton::clicked, this, &QMainWindow::close);

    layout->addWidget(victoryLabel);
    layout->addWidget(closeButton);

    stackedWidget->addWidget(victoryScreen);
    stackedWidget->setCurrentWidget(victoryScreen);

    if (gameTimer && gameTimer->isActive()) {
        gameTimer->stop();
    }
}

void MainWindow::handleGameError(const QString& errorMessage)
{
    QMessageBox::critical(this,
                          "Game Error",
                          errorMessage,
                          QMessageBox::Ok);

    stackedWidget->setCurrentWidget(startScreen);

    if (gameTimer && gameTimer->isActive()) {
        gameTimer->stop();
    }
    elapsedSeconds = 0;
    stopwatchLabel->setText("00:00");
}
