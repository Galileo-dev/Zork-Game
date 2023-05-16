#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include "../../controller/Enum.h"

#include <iostream>
MainWindow::MainWindow(GameController *gameController, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
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
    // ====================================================================================
}

void MainWindow::InputHandler(UI_INPUT ui_input, std::unordered_map<std::string, std::string> params)
{
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

    m_gameController->guiUpdateGameModel(ui_input, params);
    // call signal

    // show command ran in terminal
    // switch (ui_input)
    // {
    // case UI_INPUT::ParseCommand:
    //     ui->terminalBox->append(QString::fromStdString(">" + params["input"]));
    //     break;

    // case Action::StartGame:
    //     ui->stackedWidget->setCurrentIndex(1);
    //     break;
    // default:
    //     break;
    // }

    // clear input
    // ui->terminalInput->clear();

    // update game state
}

// in my mind this will be used to update the view
// the game model will have a string that refers to the
// recent action that was taken and the view will update
void MainWindow::updateGUIView(GameModel *gameModel)
{
}

string MainWindow::getTerminalOutput(GameModel *gameModel)
{
    // build a string
    string output = "";
    // output += "You are in room " + m_gameState.getCurentRoom()->shortDescription() + "\n";
    output += gameModel->getReaction() + "\n";
    return output;
}

void MainWindow::updateCLIView(GameModel *gameModel)
{
    std::string terminalOutput = getTerminalOutput(gameModel);
    ui->terminalBox->append(QString::fromStdString(terminalOutput));
}

MainWindow::~MainWindow()
{
    delete ui;
}
