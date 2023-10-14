#include <QtWidgets>
#include <QMessageBox>
#include <vector>
#include "gameui.h"
#include "blockui.h"

GameUi::GameUi(int size, QWidget *parent)
    : GameUi::GameUi(size, size, parent) {}

GameUi::GameUi(int row, int col, QWidget *parent)
    : QWidget(parent)
    , m_row(row)
    , m_col(col)
    , blockCollection()
    , m_game(row, col)
{
    /** Score Label */
    scoreLabel = new QLabel(tr("Score: 0"));
    scoreLabel->setAlignment(Qt::AlignCenter);
    QFont scoreFont = scoreLabel->font();
    scoreFont.setPointSize(40);
    scoreLabel->setFont(scoreFont);

    /** Side Buttons */
    closeButton = new QPushButton(tr("Exit"));
    closeButton->setFixedSize(300, 200);
    closeButton->setFocusPolicy(Qt::NoFocus);
    restoreButton = new QPushButton(tr("Restore"));
    restoreButton->setFixedSize(300, 200);
    restoreButton->setFocusPolicy(Qt::NoFocus);

    QFont buttonFont = closeButton->font();
    buttonFont.setPointSize(20);
    closeButton->setFont(buttonFont);
    restoreButton->setFont(buttonFont);

    connect(restoreButton, &QPushButton::clicked, this, &GameUi::restoreBoard);
    connect(closeButton, &QPushButton::clicked, this, &GameUi::confirmExit);

    /** Layouts */
    boardLayout = new QGridLayout;
    boardLayout->setSpacing(10);

    QVBoxLayout *sideLayout = new QVBoxLayout;
    sideLayout->addWidget(scoreLabel);
    sideLayout->addStretch();
    sideLayout->addWidget(restoreButton);
    sideLayout->addWidget(closeButton);

    QVBoxLayout *boardOuterLayout = new QVBoxLayout;
    boardOuterLayout->addStretch();
    boardOuterLayout->addLayout(boardLayout);
    boardOuterLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(boardOuterLayout);
    mainLayout->addLayout(sideLayout);

    // instantiate blockUi objects
    for (int i = 0; i < m_row; ++i) {
        for (int j = 0; j < m_col; ++j) {
            BlockUi *b = new BlockUi(i, j);
            b->setFixedSize(250, 250);
            boardLayout->addWidget(b, i, j);
            blockCollection.push_back(b);
        }
    }

    // initial refresh of block Uis
    updateBlocks();

    /** connect slots to signals */
    connect(this, &GameUi::boardUpdated, &GameUi::updateScore);
    connect(this, &GameUi::boardUpdated, &GameUi::updateBlocks);

    connect(this, &GameUi::gameWin, [this]{ endGame(GameResult::Win); });
    connect(this, &GameUi::gameLose, [this]{ endGame(GameResult::Lose); });

    // configure main layout
    setLayout(mainLayout);
    setWindowTitle(tr("2048 Game"));
    resize(1300, 1000);
    setFocus();
}

void GameUi::updateBlocks() {
    const auto board = m_game.getBoard();
    int c = 0;
    for (auto &b : blockCollection) {
        b->setWeight(board[c]);
        ++c;
    }
}

void GameUi::confirmExit() {
    /* generate a messagebox for asking to exit */
    if (QMessageBox::question(this, tr("Exit"), tr("Are you sure to quit?"),
                                  QMessageBox::Yes | QMessageBox::No)
        == QMessageBox::Yes)
    {
        QApplication::quit(); // quit application
    }
}

void GameUi::restoreBoard() {
    /* ask for restore */
    int ret = QMessageBox::question(
        this,
        tr("Restore"),
        tr("Restore the game board to its previous state?\n\nRemaining chances: %1").arg(m_game.getLife()),
        QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::No) { return; }

    /* restore board */
    auto [life_exceed_flag, buffer_empty_flag] = m_game.restoreBoard();

    /* prompt user for the result */
    QString msg;
    if (buffer_empty_flag) {
        msg = tr("There is no previously saved board in the buffer.");
    } else if (life_exceed_flag) {
        msg = tr("No more chance to restore the board to its previous state.");
    } else {
        msg = tr("The board has been restored to its previous state!");
        emit boardUpdated();
    }
    QMessageBox::information(this, tr("Restore"), msg, QMessageBox::Ok);
}

void GameUi::endGame(GameResult result) {
    /* generate a messagebox for prompting user the game ended */
    QString title, msg;
    int delay;
    int score = m_game.getScore();

    if (result == GameResult::Win) {
        title = tr("Win");
        msg = tr("Congratulation!\n\nScore: %1").arg(score);
        delay = 1000;
    } else { // GameResult::Lose
        title = tr("Lose");
        msg = tr("You lose...\n\nScore: %1").arg(score);
        delay = 0;
    }

    /* display message box */
    QTimer::singleShot(delay, this, [=] {
        QMessageBox::information(this, title, msg, QMessageBox::Ok);
    });
}

void GameUi::keyPressEvent(QKeyEvent *event) {
    /* detect if arrow keys are pressed */
    Game::Direction action;
    switch(event->key()) {
    case Qt::Key_Up:
        action = Game::Direction::Up;
        break;
    case Qt::Key_Down:
        action = Game::Direction::Down;
        break;
    case Qt::Key_Left:
        action = Game::Direction::Left;
        break;
    case Qt::Key_Right:
        action = Game::Direction::Right;
        break;
    default:
        return;
    }

    /* if so, update the board with given action */
    auto [win, lose, bad] = m_game.transitionBoard(action);

    /* dispatch events corresponding the result */
    if (bad == false) {
        emit boardUpdated();
    }
    if (win == true) {
        emit gameWin();
    }
    if (lose == true) {
        emit gameLose();
    }
}

void GameUi::updateScore() {
    /* update the score label */
    scoreLabel->setText(tr("Score: %1").arg(m_game.getScore()));
}
