#include "blockui.h"
#include <tuple>

BlockUi::BlockUi(int row, int col)
    : m_row(row)
    , m_col(col)
    , m_weight(-1)
{
    setAlignment(Qt::AlignCenter);
}

void BlockUi::setWeight(int weight)
{
    if (m_weight == weight) { return; }

    m_weight = weight;
    if (weight != 0) {
        setText(QString::number(weight));
    } else {
        clear(); // this->clear();
    }

    using rgb_t = std::tuple<int, int, int>;
    rgb_t rgb;

    switch (weight) {
    case 0:
        rgb = rgb_t {255, 255, 255};
        break;
    case 2:
        rgb = rgb_t {187, 173, 160};
        break;
    case 4:
        rgb = rgb_t {237, 224, 200};
        break;
    case 8:
        rgb = rgb_t {242, 177, 121};
        break;
    case 16:
        rgb = rgb_t {245, 149, 99};
        break;
    case 32:
        rgb = rgb_t {246, 126, 95};
        break;
    case 64:
        rgb = rgb_t {246, 94, 59};
        break;
    case 128:
        rgb = rgb_t {237, 207, 114};
        break;
    case 256:
        rgb = rgb_t {237, 204, 97};
        break;
    case 512:
        rgb = rgb_t {237, 200, 80};
        break;
    case 1024:
        rgb = rgb_t {237, 197, 63};
        break;
    case 2048:
        // fall through
    default:
        rgb = rgb_t {237, 194, 46};
        break;
    }

    const auto [r, g, b] = rgb;
    setStyleSheet(
        tr("color: black; \
            border-style: solid; \
            font: 70pt; \
            font: bold; \
            background: rgb(%1, %2, %3);"
           ).arg(r).arg(g).arg(b));
}
