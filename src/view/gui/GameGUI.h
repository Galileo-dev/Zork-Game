#ifndef GameGUI_H_
#define GameGUI_H_

#include <iostream>
#include <string>
#include "../../model/Game.h"
#include <QApplication>
using namespace std;

class GameGUI
{
private:
public:
    GameGUI();
    QApplication start();
    void update(const GameModel *GameModel);
};

#endif /*GameGUI_H_*/