#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <iostream>
MainWindow::MainWindow(GameController *gameController, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    m_gameController = gameController;
    m_gameModel = gameController->GetGameModel();

    ui->setupUi(this);
    // print debug message
    std::cout << "m_gameModel: " << m_gameModel << std::endl;
    connect(m_gameModel, &GameModel::gameModelChanged, this, &MainWindow::updateView);

    // start new game
    connect(ui->startButton, &QPushButton::clicked, this, [=]()
            {
                unordered_map<string, string> params = {{"difficulty", ui->modeSelectionInput->currentText().toStdString()}, {"player_name", ui->characterNameInput->text().toStdString()}};
                 InputHandler(Action::StartGame, params); });

    // command line input
    connect(ui->terminalInput, &QLineEdit::returnPressed, this, [=]()
            {
        std::string input = ui->terminalInput->text().toStdString();
        InputHandler(Action::ParseCommand, {{"input", input}}); });
}

void MainWindow::InputHandler(Action action, std::unordered_map<std::string, std::string> params)
{
    std::cout << "MainWindow::InputHandler()" << std::endl;
    // action
    std::cout << "action: " << action << std::endl;
    // params
    std::cout << "params: " << std::endl;
    for (auto &param : params)
    {
        std::cout << param.first << ": " << param.second << ",";
        std::cout << std::endl;
    }
    // call signal

    // show command ran in terminal
    switch (action)
    {
    case Action::ParseCommand:
        ui->terminalBox->append(QString::fromStdString(">" + params["input"]));
        break;

    default:
        break;
    }

    // clear input
    ui->terminalInput->clear();

    // update game state
    m_gameController->updateGameState(action, params);
}

// in my mind this will be used to update the view
// the game model will have a string that refers to the
// recent action that was taken and the view will update
void MainWindow::updateView(GameModel *gameModel)
{
    std::cout << "MainWindow::updateView()" << std::endl;

    // terminal view
    std::string terminalOutput = gameModel->getTerminalOutput();

    ui->terminalBox->append(QString::fromStdString(terminalOutput));

    gameModel->updatedView();
}

MainWindow::~MainWindow()
{
    delete ui;
}
