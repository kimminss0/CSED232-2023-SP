#include "game.h"

Game::Logger::Logger(std::string filename)
    : m_file(filename)
{
}

Game::Logger::~Logger() {
    m_file.close();
}

void Game::Logger::logInitialized(int x1, int y1, int x2, int y2) {
    m_file << "INITIAL "
           << x1 + 1 << " "
           << y1 + 1 << " "
           << x2 + 1 << " "
           << y2 + 1 << std::endl;
}

void Game::Logger::logAction(Direction a) {
    if (a == Direction::Up) {
        m_file << "UP";
    } else if (a == Direction::Down) {
        m_file << "DOWN";
    } else if (a == Direction::Left) {
        m_file << "LEFT";
    } else { // Direction::Right
        m_file << "RIGHT";
    }
    m_file << std::endl;
}

void Game::Logger::logGenerated(int x, int y, int n) {
    m_file << "GENERATE "
           << x + 1 << " "
           << y + 1 << " "
           << n << std::endl;
}

void Game::Logger::logMerged(int x, int y, int n) {
    m_file << "MERGE "
           << x + 1 << " "
           << y + 1 << " "
           << n << std::endl;
}

void Game::Logger::logRestored(int remain_life) {
    m_file << "RESTORE " << remain_life << std::endl;
}

void Game::Logger::logScore(int score) {
    m_file << "SCORE " << score << std::endl;
}

Game::Game(int row, int col, int life)
    : m_logger()
    , m_life(life)
    , m_row(row)
    , m_col(col)
    , m_score{0}
    , m_gen(std::random_device()())
    , m_board(row, col, m_gen)
{
    auto [pos1, pos2] = m_board.init();
    auto [x1, y1] = pos1;
    auto [x2, y2] = pos2;
    m_logger.logInitialized(x1, y1, x2, y2);
}

Game::TransitionResult Game::transitionBoard(Direction action) {
    auto [
        win_flag, // weight reached to the goal
        lose_flag, // cannot move block anymore
        bad_flag, // no move occured
        generated, // position of generated block
        merged // vector consists of positions of merged block, ordered by pos
    ] = m_board.transition(action);

    // log
    m_logger.logAction(action);

    if (!bad_flag) {
        // update score
        int score = getScore();
        for (const auto &pos : merged) {
            int w = m_board.getBlock(pos);
            auto [x, y] = pos;
            // log merged
            m_logger.logMerged(x, y, w);
            score += w;
        }
        m_score.push_back(score);
        if (m_score.size() == 3) {
            m_score.pop_front();
        }

        // log generated
        auto [x, y] = generated;
        m_logger.logGenerated(x, y, m_board.getBlock(x, y));

        // log score
        m_logger.logScore(getScore());
    }

    return { win_flag, lose_flag, bad_flag };
}

Game::RestoreResult Game::restoreBoard() {
    if (m_life == 0) {
        return {true, false};
    }

    bool success = m_board.restore();
    if (success) {
        --m_life;
        m_score.pop_back();
        m_logger.logRestored(m_life);
    }
    return {false, !success};
}

std::vector<int> Game::getBoard() {
    std::vector<int> board;
    board.reserve(m_row * m_col);
    for (int i = 0; i < m_row; ++i) {
        for (int j = 0; j < m_col; ++j) {
            board.emplace_back(m_board.getBlock(i, j));
        }
    }
    return board;
}

