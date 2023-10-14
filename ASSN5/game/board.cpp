#include "board.h"

#include <algorithm>

Board::Board(int row, int col, gen_t gen)
    : m_row(row)
    , m_col(col)
    , m_win_received(false)
    , m_dis(0., 1.)
    , m_gen(gen)
{
    m_buffer.push_back(flatboard_t(m_row * m_col));
}

inline Board::flatboard_t &Board::getBoard() {
    return m_buffer.back();
}

inline int Board::getRandomWeight() {
    const double x = m_dis(m_gen);

    // probability
    // 4 : 20%
    // 2 : 80%
    return (x < 0.2) ? 4 : 2;
}

inline Block *Board::_getBlock(const pos_t &pos) {
    return _getBlock(std::get<0>(pos), std::get<1>(pos));
}

inline Block *Board::_getBlock(int row, int col) {
    return &(getBoard()[m_col * row + col]);
}

int Board::getBlock(const pos_t &pos) {
    return _getBlock(pos)->weight;
}

int Board::getBlock(int row, int col) {
    return _getBlock(row, col)->weight;
}

inline bool Board::isPosValid(const pos_t &pos) {
    return isPosValid(std::get<0>(pos), std::get<1>(pos));
}

inline bool Board::isPosValid(int row, int col) {
    return row >= 0 && row < m_row && col >= 0 && col < m_col;
}

inline Board::pos_t Board::getBackward(const pos_t &pos, Direction d) {
    const auto [row, col] = pos;
    if (d == Direction::Up) {
        return {row + 1, col};
    } else if (d == Direction::Down) {
        return {row - 1, col};
    } else if (d == Direction::Left) {
        return {row, col + 1};
    } else { // Direction::Right
        return {row, col - 1};
    }
}

bool Board::restore() {
    if (m_buffer.size() == 1) {
        return false;
    }
    m_buffer.pop_back();
    return true;
}

Board::InitResult Board::init() {
    const int initWeight = 2;
    const int mod1 = m_row * m_col;
    const int mod2 = mod1 - 1;

    // chose 2 number between 0~15
    double x = m_dis(m_gen);
    int n1 = std::clamp(int(x * mod1), 0, mod1);

    x = m_dis(m_gen);
    int n2 = std::clamp(int(x * mod2), 0, mod2);
    if (n2 >= n1) {
        ++n2;
    } else {
         std::swap(n1, n2);
    } // follows order

    // convert to position
    const pos_t pos1 = {n1 / m_col, n1 % m_col};
    const pos_t pos2 = {n2 / m_col, n2 % m_col};

    // set weight, flags of Block
    Block *b1 = _getBlock(pos1);
    Block *b2 = _getBlock(pos2);
    b1->weight = initWeight;
    b1->generated = true;
    b2->weight = initWeight;
    b2->generated = true;

    return InitResult{pos1, pos2};
}

Board::TransitionResult Board::transition(Direction d) {
    const int weight_goal = 2048;
    TransitionResult res;
    auto &[
        win_flag, // weight reached to the goal
        lose_flag, // cannot move block anymore
        bad_flag, // no move occured
        generated, // position of generated block
        merged // vector consists of positions of merged block, ordered by pos
    ] = res;
    win_flag = false;
    lose_flag = true;
    bad_flag = true;
    generated = {-1, -1};

    // duplicate board on buffer
    m_buffer.push_back(getBoard());

    // stage 1: move
    /**
     * heads: vector consists of 'head' positions
     *
     * from 'head', travel against the direction d,
     * and if the block of nonzero weight has found,
     * push toward the direction d.
     * if available, merge blocks.
     */
    std::vector<pos_t> heads{};
    if (d == Direction::Up) {
        for (int i = 0; i < m_col; ++i) {
            heads.push_back(pos_t(0, i));
        }
    } else if (d == Direction::Down) {
        for (int i = 0; i < m_col; ++i) {
            heads.push_back(pos_t(m_row - 1, i));
        }
    } else if (d == Direction::Left) {
        for (int i = 0; i < m_row; ++i) {
            heads.push_back(pos_t(i, 0));
        }
    } else { // Direction::Right
        for (int i = 0; i < m_row; ++i) {
            heads.push_back(pos_t(i, m_col - 1));
        }
    }

    for (const pos_t &head : heads) {
        pos_t dest = head;
        pos_t target = dest;
        while (isPosValid(target)) {
            Block *tg = _getBlock(target);
            tg->merged = false;
            tg->generated = false;
            if (target == dest || !tg->weight) {
                target = getBackward(target, d);
                continue;
            }
            if (_getBlock(dest)->weight == tg->weight) {
                /* merge */
                Block *dt = _getBlock(dest);
                const int new_weight = tg->weight * 2;

                // manipulate Block
                dt->weight = new_weight;
                dt->merged = true;
                tg->weight = 0;

                // configure next iteration
                dest = getBackward(dest, d);
                target = getBackward(target, d);

                // set flags
                win_flag |= !m_win_received && (new_weight == weight_goal);
                bad_flag = false;
            } else if (!_getBlock(dest)->weight) {
                /* move without merge */
                Block *dt = _getBlock(dest);

                // manipulate Block
                dt->weight = tg->weight;
                tg->weight = 0;

                // configure next iteration
                target = getBackward(target, d);

                // set flags
                bad_flag = false;
            } else {
                dest = getBackward(dest, d);
            }

        }
    }
    if (win_flag) { m_win_received = true; }

    // stage 2: find merged block
    // stage 3: generate new block
    std::vector<pos_t> empty;
    {
        int c = 0;
        const flatboard_t &board = getBoard();
        for (const Block &b : board) {
            const int row = c / m_col;
            const int col = c % m_col;
            if (!b.weight) {
                empty.push_back({row, col});
            } else if (b.merged) {
                merged.push_back({row, col});
            }

            // check for lose_flag
            if (lose_flag) {
                if (b.weight == 0) {
                    lose_flag = false;
                } else {
                    for (Direction d : {Direction::Up, Direction::Down, Direction::Left, Direction::Right}) {
                        pos_t p  = getBackward({row, col}, d);
                        if (isPosValid(p) && _getBlock(p)->weight == b.weight) {
                            lose_flag = false;
                            break;
                        }
                    }
                }
            }
            ++c;
        }
    }
    const int emptyCnt = empty.size();

    if (!bad_flag) {
        // generate a block unless no blocks were moved
        const double p = m_dis(m_gen);
        generated = empty[std::clamp(int(p * emptyCnt), 0, emptyCnt)];
        Block *b = _getBlock(generated);
        *b = {getRandomWeight(), false, true};

        if (m_buffer.size() == 3) {
            // remove old board from buffer
            m_buffer.pop_front();
        }
    } else {
        // remove last added
        m_buffer.pop_back();
    }

    return res;
}
