#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <QObject>
#include "../model/GameState.h"

class GameModel : public QObject
{
    Q_OBJECT

public:
    GameModel(QObject *parent = nullptr);
    const GameState &gameState();
    void updateGameState();
signals:
    void gameStateChanged(const GameState &gameState);

private:
    GameState m_gameState;
};

#endif // GAME_MODEL_H