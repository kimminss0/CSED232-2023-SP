#ifndef GAMEUI_H
#define GAMEUI_H

#include <QWidget>
#include <QtWidgets>

#include "game/game.h"
#include <vector>
#include "blockui.h"

QT_BEGIN_NAMESPACE
class QPushButton;
class QLabel;
QT_END_NAMESPACE

class GameUi : public QWidget
{
    Q_OBJECT

public:
    GameUi(int size = 4, QWidget *parent = nullptr);
    GameUi(int row, int col, QWidget *parent = nullptr);
    enum class GameResult{ Win, Lose };

public slots:
    void confirmExit();
    void restoreBoard();
    void updateScore();
    void updateBlocks();

signals:
    void boardUpdated();
    void gameWin();
    void gameLose();

private:
    void endGame(GameResult result);

    const int m_row, m_col;
    std::vector<BlockUi *> blockCollection;
    Game m_game;
    QLabel *scoreLabel;
    QPushButton *closeButton;
    QPushButton *restoreButton;
    QGridLayout *boardLayout;

protected:
    void keyPressEvent(QKeyEvent *event);
};
#endif // GAMEUI_H
