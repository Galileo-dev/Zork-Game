#ifndef GAME_GUI_H
#define GAME_GUI_H

#include <QApplication>
#include <QWidget>
#include "../../model/GameState.h"

class GameState;
class MainWindow;

struct InputArgs
{
    int argc;
    char **argv;
};

class GameGUI
{
public:
    GameGUI();

    // Must be called on the main thread
    // void setup();

    // Can be called on any thread

    void start(InputArgs &);

    void update(const GameState *gameModel);

private:
};
#endif // GAME_GUI_H
