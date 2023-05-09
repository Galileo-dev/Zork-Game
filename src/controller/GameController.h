#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include "../model/GameModel.h"

class GameController : public QObject
{
    Q_OBJECT
public:
    GameController(QObject *parent = nullptr);
    GameModel *GetGameModel() { return &m_gameModel; }

public slots:
    void updateGameState(Action action, std::unordered_map<std::string, std::string> params);

private:
    GameModel m_gameModel;
};

#endif // GAMECONTROLLER_H