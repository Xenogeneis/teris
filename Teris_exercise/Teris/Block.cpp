#include "Block.h"
//block layout is : {h - 1, w - 1} {x0, y0} {x1, y1} {x2, y2} {x3, y3} (two bits each)
// e.g.:
// 431424: 0110 1001 0101 0100 0000 
// 598356: 1001 0010 0001 0101 0100
// 427089: 0110 1000 0100 0101 0001
// 247872: 0011 1100 1000 0100 0000
// 799248: 1100 0011 0010 0001 0000
// 348480: 0101 0101 0001 0100 0000
// 
// (0,0)
// ----------->x, w  coordinate system
// |
// |
// |
// V
// y,h
//   ..  -> 431424
//  ..
//  ..   -> 348480
//  ..
//  .... -> 247872
//  .    -> 799248
//  .
//  .
//  .
const int Block::BLOCK_DATA[Block::TYPE_NUM][4] =
{ {431424, 598356, 431424, 598356},
  {427089, 615696, 427089, 615696},
  {348480, 348480, 348480, 348480},
  {599636, 431376, 598336, 432192},
  {411985, 610832, 415808, 595540},
  {247872, 799248, 247872, 799248},
  {614928, 399424, 615744, 428369} };   // 方块数据，对象共享的资源
//block colors
const COLORREF Block::COLORS[Block::TYPE_NUM] =
{ 0x0789dd, 0x7f5605, 0xfc721e, 0x0f2e8a, 0xbebd20, 0xe72019, 0x76196b };

Block::Block(vector<int>& m, const int& x, const int& y) : m_x(x), m_y(y), m_map(m) {
    randType();
}

bool Block::move(const Dir& direction) {
    switch (direction) {
    case DOWN:
        if (checkCollision(m_x, m_y + 1))
            return true;
        m_y++;
        break;
    case LEFT:
        if (!checkCollision(m_x - 1, m_y))
            m_x--;
        break;
    case RIGHT:
        if (!checkCollision(m_x + 1, m_y))
            m_x++;
        break;
    }
    return false;
}

void Block::draw(int leftX, int leftY) const {
    // draw current block
    ///////////////////////////////////////////////////
    // BEGIN OF YOUR CODE
    ///////////////////////////////////////////////////
    for (int i = 0; i < m_map.size(); ++i) {
        if (m_map[i] != 0) {
            // 计算方块在窗口中的位置
            int x = leftX + (i % LEFT) * BLOCK_SIZE;
            int y = leftY + (i / LEFT) * BLOCK_SIZE;

            // 设置方块颜色
            COLORREF color;
            switch (m_map[i]) {
            case 1: color = RED; break;
            case 2: color = GREEN; break;
            case 3: color = BLUE; break;
            case 4: color = YELLOW; break;
            case 5: color = CYAN; break;
            case 6: color = MAGENTA; break;
            case 7: color = LIGHTGRAY; break;
            default: color = BLACK; break;
            }
            setfillcolor(color);

            // 绘制方块
            solidrectangle(x, y, x + BLOCK_SIZE - 1, y + BLOCK_SIZE - 1);
        }
    }
    ///////////////////////////////////////////////////
    // END OF YOUR CODE
    ///////////////////////////////////////////////////
}

void Block::clear(int leftX, int leftY) const {
    int x, y, left, top;
    for (int i = 0; i < 4; i++) {
        x = getX(i);
        y = getY(i);
        left = leftX + BLOCK_SIZE * (m_x + x);
        top = leftY + BLOCK_SIZE * (m_y + y);
        clearrectangle(left, top, left + BLOCK_SIZE, top + BLOCK_SIZE);
    }
}

void Block::rotate() {
    int ori_ind = m_ind, ori_x = m_x;
    m_ind = (m_ind + 1) % 4;
    while (m_x + blkWd() >= MAP_WIDTH)
        m_x--;
    if (checkCollision()) {
        m_ind = ori_ind;
        m_x = ori_x;
    }

}
bool Block::checkCollision() const {
    return checkCollision(m_x, m_y);
}
bool Block::checkCollision(int x, int y) const {
    if (x < 0 ||
        x + blkWd() >= MAP_WIDTH ||
        y + blkHt() >= MAP_HEIGHT)
        return true;

    int bx, by;
    for (int i = 0; i < 4; i++) {
        bx = getX(i);
        by = getY(i);
        if (m_map[(y + by) * MAP_WIDTH + x + bx])
            return true;
    }
    return false;
}

void Block::setPos(const int& x, const int& y) {
    this->m_x = x;
    this->m_y = y;
}

void Block::randType() {
    // generate new type of block
    ///////////////////////////////////////////////////
    // BEGIN OF YOUR CODE
    ///////////////////////////////////////////////////
     // 随机生成新的方块类型
    m_type = rand() % TYPE_NUM; // 假设 TYPE_NUM 是方块类型的数量
    m_ind = rand() % 4; // 四个可能的方向

    // 根据方块类型和方向，设置方块的形状
    int blockCode = BLOCK_DATA[m_type][m_ind];
    m_map.clear();
    m_map.resize(16, 0); // 假设方块形状在4x4的网格中

    // 解析方块编码，设置方块形状
    for (int i = 0; i < 4; ++i) {
        // 每个坐标占两位，从编码中提取坐标
        int x = (blockCode >> (i * 4)) & 0x3;
        int y = (blockCode >> (i * 4 + 2)) & 0x3;
        m_map[y * 4 + x] = 1; // 在对应位置放置方块的一部分
    }

    // 设置方块颜色
    COLORS[m_type];
    ///////////////////////////////////////////////////
    // END OF YOUR CODE
    ///////////////////////////////////////////////////
}
Block& Block::operator=(const Block& rhs) {
    m_type = rhs.m_type;
    m_ind = rhs.m_ind;
    m_map = rhs.m_map;
    return *this;
}
