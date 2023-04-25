#include "Game.h"
#include "GameGUI.h"
#include "./MainWindow.h"
#include <iostream>
#include <string>

#include <QTimer>
#include <QThread>
using namespace std;

GameGUI::GameGUI()
{
    // TODO Auto-generated constructor stub
}

// must run on main thread
void *setup(void *threadArg)
{
    int argc = 0;
    char *argv[1] = {nullptr};

    // create the QApplication instance
    QApplication app(argc, argv);

    // create and show the main window
    QMainWindow mainWindow;
    mainWindow.show();
    app.exec();
    pthread_exit(NULL);
}

// can run on any thread
void GameGUI::start(InputArgs &args)
{
    pthread_t thread1;
    int rc = pthread_create(&thread1, NULL, setup, (void *)&args);
}

void GameGUI::update(const GameModel *GameModel)
{
    // TODO Auto-generated method stub
}