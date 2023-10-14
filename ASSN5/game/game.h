#ifndef GAME_H
#define GAME_H

#include "board.h"
#include <QObject>

#include <vector>
#include <fstream>
#include <string>

class Game : public QObject
{
    Q_OBJECT

public:
    // type definition
    typedef typename Board::Direction Direction;

    struct TransitionResult {
        bool win, lose, bad;
    };

    struct RestoreResult {
        bool life_exceed_flag;
        bool buffer_empty_flag;
    };

    // ctor
    Game(int row, int col, int life = 3);

    // member declaration
    TransitionResult transitionBoard(Direction action);
    RestoreResult restoreBoard();
    std::vector<int> getBoard();
    int getLife() { return m_life; }
    int getScore() { return m_score.back(); }
    int getRow() { return m_row; }
    int getCol() { return m_col; }

private:
    class Logger
    {
    public:
        // ctor & dtor
        Logger(std::string filename = "progress.txt");
        ~Logger();

        // member declaration
        void logInitialized(int x1, int y1, int x2, int y2);
        void logAction(Direction a);
        void logGenerated(int x, int y, int n);
        void logMerged(int x, int y, int n);
        void logRestored(int remain_life);
        void logScore(int score);

    private:
        std::ofstream m_file;
    };

    Logger m_logger;
    int m_life;
    int m_row, m_col;
    std::deque<int> m_score;
    gen_t m_gen;
    Board m_board;
};

#endif // GAME_H
