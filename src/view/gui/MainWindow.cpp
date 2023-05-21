#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include "../../controller/Enum.h"
#include <iostream>

MainWindow::MainWindow(GameController *gameController, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // audio stuff
    player = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl::fromLocalFile(QCoreApplication::applicationDirPath() + "/Atomic Heart OST.mp3"));
    audioOutput->setVolume(50);
    player->play();

    // initialise ui
    m_gameController = gameController;
    m_gameModel = gameController->GetGameModel();
    ui->setupUi(this);

    // ========================== Connecting UI to GameController ==========================

    connect(m_gameModel, &GameModel::gameModelChanged, this, &MainWindow::updateGUIView);
    connect(m_gameModel, &GameModel::gameModelChanged, this, &MainWindow::updateCLIView);
    // start new game
    connect(ui->startButton, &QPushButton::clicked, this, [=]()
            {
                unordered_map<string, string> params = {{"difficulty", ui->modeSelectionInput->currentText().toStdString()}, {"player_name", ui->characterNameInput->text().toStdString()}};
                 InputHandler(UI_INPUT::StartGame, params); });

    // command line input
    connect(ui->terminalInput, &QLineEdit::returnPressed, this, [=]()
            {
        std::string input = ui->terminalInput->text().toStdString();
        ui->terminalInput->clear();
        ui->terminalBox->append(QString::fromStdString(">" + input));
        InputHandler(UI_INPUT::CommandEntered, {{"input", input}}); });

    // north button
    connect(ui->northButton, &QPushButton::clicked, this, [=]()
            { InputHandler(UI_INPUT::Go, {{"direction", "north"}}); });
    // south button
    connect(ui->southButton, &QPushButton::clicked, this, [=]()
            { InputHandler(UI_INPUT::Go, {{"direction", "south"}}); });
    // east button
    connect(ui->eastButton, &QPushButton::clicked, this, [=]()
            { InputHandler(UI_INPUT::Go, {{"direction", "east"}}); });
    // west button
    connect(ui->westButton, &QPushButton::clicked, this, [=]()
            { InputHandler(UI_INPUT::Go, {{"direction", "west"}}); });

    // drop an item
    connect(ui->playerItemsList, &QListWidget::itemDoubleClicked, this, [=]()
            { InputHandler(UI_INPUT::DropItem, {{"item_name", ui->playerItemsList->currentItem()->data(Qt::UserRole).toString().toStdString()}}); });
    
    //pickup an item
    connect(ui->roomItemsList, &QListWidget::itemDoubleClicked, this, [=]()
            { InputHandler(UI_INPUT::PickupItem, {{"item_name", ui->roomItemsList->currentItem()->data(Qt::UserRole).toString().toStdString()}}); });

    //solve a riddle
    connect(ui->riddleAnswerInput, &QLineEdit::returnPressed, this, [=]()
            {
        std::string riddleAnswer = ui->riddleAnswerInput->text().toStdString();
        InputHandler(UI_INPUT::SolveRiddle, {{"riddle_answer", riddleAnswer}}); });

    // ====================================================================================

    // model view controller pattern
    emit m_gameModel->gameModelChanged(m_gameModel);
}

void MainWindow::InputHandler(UI_INPUT ui_input, std::unordered_map<std::string, std::string> params)
{
// only for debugging. will only show when the DEBUG_LOG flag is defined in the CMakeLists.txt
#ifdef DEBUG_LOG
    std::cout << "MainWindow::InputHandler()" << std::endl;
    std::cout << "input: " << static_cast<std::underlying_type<UI_INPUT>::type>(ui_input) << std::endl;
    std::cout << "params: " << std::endl;
    for (auto &param : params)
    {
        std::cout << param.first << ": " << param.second << ",";
        std::cout << std::endl;
    }
#endif

    // handle ui input
    m_gameController->guiUpdateGameModel(ui_input, params);
}

// in my mind this will be used to update the view
// the game model will have a string that refers to the
// recent action that was taken and the view will update
void MainWindow::updateGUIView(GameModel *gameModel)
{
    // if the character is created then we can start the game
    if (gameModel->getCharacter() != nullptr)
    {
        // do character & game settings stuff in here
        ui->stackedWidget->setCurrentIndex(1);

        // update player inventory list
        ui->playerItemsList->clear();
        for (auto &item : gameModel->getCharacter()->getInventory())
        {
            QListWidgetItem *newItem = new QListWidgetItem;
            // we need to store item identifier as that is what the master list uses
            newItem->setData(Qt::UserRole, QString::fromStdString(item->getIdentifier()));
            newItem->setText(QString::fromStdString(item->getDisplayName()));
            ui->playerItemsList->addItem(newItem);
        }

        // update room inventory list
        ui->roomItemsList->clear();

        // if room is item room
        ItemRoom *itemRoom = dynamic_cast<ItemRoom *>(gameModel->getCurentRoom());
        if (itemRoom != nullptr)
        {
            for (auto &item : itemRoom->getItems())
            {
                // show items in room on ui
                QListWidgetItem *newItem = new QListWidgetItem;
                newItem->setData(Qt::UserRole, QString::fromStdString(item->getIdentifier()));
                newItem->setText(QString::fromStdString(item->getDisplayName()));
                ui->roomItemsList->addItem(newItem);
            }
        }
    }

    // disable buttons if there is no room in that direction
    ExitRoom *exitRoom = dynamic_cast<ExitRoom *>(gameModel->getCurentRoom());
    // check it has exits
    if (exitRoom == nullptr)
    {
        ui->northButton->setEnabled(false);
        ui->southButton->setEnabled(false);
        ui->eastButton->setEnabled(false);
        ui->westButton->setEnabled(false);
    }
    else
    {

        ui->northButton->setEnabled(exitRoom->getRoom(Direction::NORTH) != NULL);
        ui->southButton->setEnabled(exitRoom->getRoom(Direction::SOUTH) != NULL);
        ui->eastButton->setEnabled(exitRoom->getRoom(Direction::EAST) != NULL);
        ui->westButton->setEnabled(exitRoom->getRoom(Direction::WEST) != NULL);
    }

    // update the text box
    ui->outputText->append(QString::fromStdString(gameModel->getReaction()));
}

string MainWindow::getTerminalOutput(GameModel *gameModel)
{
    string output = "";
    // reaction system is the same for both gui and cli making it agnostic to the type of view
    output += gameModel->getReaction();
    return output;
}

void MainWindow::updateCLIView(GameModel *gameModel)
{
    // just add the terminal output to the terminal box
    std::string terminalOutput = getTerminalOutput(gameModel);
    ui->terminalBox->append(QString::fromStdString(terminalOutput));
}

MainWindow::~MainWindow()
{
    delete ui;
}
