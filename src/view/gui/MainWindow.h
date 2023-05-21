#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAudioOutput>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

#include "../../controller/GameController.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(GameController *GameController, QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // this function is called when the windows appears by Qt
    void showEvent(QShowEvent *event) override
    {
        QMainWindow::showEvent(event);

// for debugging purposes create a new game on startup
#ifdef DEBUG_LOG

        unordered_map<string, string> params = {{"difficulty", "Cursed"}, {"player_name", "Player"}};
        InputHandler(UI_INPUT::StartGame, params);
#endif
    }

private:
    Ui::MainWindow *ui;
    GameController *m_gameController;
    GameModel *m_gameModel;
    string getTerminalOutput(GameModel *gameModel);

    // audio players
    QMediaPlayer *player;
    QAudioOutput *audioOutput;

private slots:
    // slots are defined for qt to connect to
    void InputHandler(UI_INPUT ui_input, std::unordered_map<std::string, std::string> params);
    void updateGUIView(GameModel *gameModel);
    void updateCLIView(GameModel *gameModel);
};
#endif // MAINWINDOW_H
