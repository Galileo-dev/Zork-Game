#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include "Enum.h"
#include "../model/GameModel.h"

class GameController : public QObject
{
    Q_OBJECT
public:
    GameController(QObject *parent = nullptr);
    GameModel *GetGameModel() { return &m_gameModel; }

public slots:
    void guiUpdateGameModel(UI_INPUT ui_input, std::unordered_map<std::string, std::string> params);
    void cliUpdateGameModel(std::string Command);

private:
    GameModel m_gameModel;
};

#endif // GAMECONTROLLER_H