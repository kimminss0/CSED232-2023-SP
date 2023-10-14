#ifndef BLOCKUI_H
#define BLOCKUI_H

#include <QLabel>

class BlockUi : public QLabel
{
    Q_OBJECT
public:
    BlockUi(int row, int col);

public slots:
    void setWeight(int weight);

private:
    int m_row, m_col;
    int m_weight;
};

#endif // BLOCKUI_H
