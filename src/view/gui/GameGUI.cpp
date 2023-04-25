#include "Game.h"
#include "GameGUI.h"
#include "./MainWindow.h"
#include <iostream>
#include <string>
#include <QApplication>
#include <QWidget>
#include <QTimer>

using namespace std;

class GameGUI : public QWidget
{
    Q_OBJECT
public:
    explicit GameGUI(QWidget *parent = nullptr) : QWidget(parent)
    {
        // Set up the widget
        setFixedSize(400, 400);
        // Create a timer to run the game loop
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &GameGUI::gameLoop);
        timer->start(16); // 60 FPS (1000 ms / 60 = 16.67 ms)
    }

private:
    void gameLoop()
    {
        // Update the game state
        // ...
        // Render the game
        // ...
        // print the game
        cout << "start" << endl;
    }
};
