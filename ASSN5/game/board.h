#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <array>
#include <queue>
#include <tuple>
#include <random>
#include "block.h"

using gen_t = std::mt19937;


class Board
{
public:
    // type definition
    enum class Direction { Up, Down, Left, Right };

    typedef typename std::tuple<int, int> pos_t;
    typedef typename std::vector<Block> flatboard_t;
    typedef typename std::array<pos_t, 2> InitResult;

    struct TransitionResult {
        bool win_flag;
        bool lose_flag;
        bool bad_flag;
        pos_t generated;
        std::vector<pos_t> merged;
    };

    // ctor
    Board(int row, int col, gen_t gen);

    // member declaration
    InitResult init();
    TransitionResult transition(Direction d);
    int getBlock(const pos_t &pos);
    int getBlock(int row, int col);
    bool restore();

private:
    int getRandomWeight();
    Block *_getBlock(const pos_t &pos);
    Block *_getBlock(int row, int col);
    bool isPosValid(const pos_t &pos);
    bool isPosValid(int row, int col);
    pos_t getBackward(const pos_t &pos, Direction d);
    flatboard_t &getBoard();

    const int m_row;
    const int m_col;

    bool m_win_received;
    std::deque<flatboard_t> m_buffer;
    std::uniform_real_distribution<double> m_dis;
    gen_t m_gen;
};

#endif // BOARD_H
