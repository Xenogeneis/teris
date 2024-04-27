#pragma once
#include <cstdint>
#include <easyx.h>
#include <vector>
#include "Globals.h"
using namespace std;
class Game;
// 方块类
class Block
{
public:
    enum Dir {
        DOWN = 0, LEFT, RIGHT
    };
public:
    // 初始化函数
    Block(vector<int>&, const int& x = (MAP_WIDTH - 4) / 2, const int& y = 0);
    void draw(int leftX, int leftY) const;                             // 绘制函数
    void clear(int leftX, int leftY) const;                            // 清除函数
    void rotate();                                                              // 旋转方块，false 向左，true 向右
    bool checkCollision() const;                                    // 碰撞检查
    bool checkCollision(int x, int y) const;                                    // 碰撞检查
    void setPos(const int& x = (MAP_WIDTH - 4) / 2, const int& y = 0);    // 设置方块坐标
    void randType();                                                            // 随机方块类型
    bool moveDown() { return move(DOWN); }
    void moveLeft() { move(LEFT); }
    void moveRight() { move(RIGHT); }

    COLORREF color() const { return COLORS[m_type]; }
    int x() const { return m_x; }
    int y() const { return m_y; }
    int type() const { return m_type + 1; }
    int blkWd() const { return 3 & (BLOCK_DATA[m_type][m_ind] >> 16); }
    int blkHt() const { return 3 & (BLOCK_DATA[m_type][m_ind] >> 18); }

    // Get the 'ind'th point coord of this block
    ///////////////////////////////////////////////////
    // BEGIN OF YOUR CODE
    ///////////////////////////////////////////////////

    // do not modify the signature of these two function
    int getX(int ind) const { return 0; }
    int getY(int ind) const { return 0; }
    ///////////////////////////////////////////////////
    // END OF YOUR CODE
    ///////////////////////////////////////////////////


    Block& operator=(const Block& rhs);
private:
    // 移动函数，0 表示下移一格，1 表示左移一格，2 表示右移一格，当下移检测到碰撞时返回 true
    bool move(const Dir& direction);
private:
    int m_x;                  // 方块 X 坐标
    int m_y;                  // 方块 Y 坐标
    int m_type;               // 方块类型
    int m_ind;
    const static int TYPE_NUM = 7;
    const static int BLOCK_DATA[TYPE_NUM][4];
    vector<int>& m_map;
public:
    const static COLORREF COLORS[TYPE_NUM];
};
