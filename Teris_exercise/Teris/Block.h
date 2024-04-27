#pragma once
#include <cstdint>
#include <easyx.h>
#include <vector>
#include "Globals.h"
using namespace std;
class Game;
// ������
class Block
{
public:
    enum Dir {
        DOWN = 0, LEFT, RIGHT
    };
public:
    // ��ʼ������
    Block(vector<int>&, const int& x = (MAP_WIDTH - 4) / 2, const int& y = 0);
    void draw(int leftX, int leftY) const;                             // ���ƺ���
    void clear(int leftX, int leftY) const;                            // �������
    void rotate();                                                              // ��ת���飬false ����true ����
    bool checkCollision() const;                                    // ��ײ���
    bool checkCollision(int x, int y) const;                                    // ��ײ���
    void setPos(const int& x = (MAP_WIDTH - 4) / 2, const int& y = 0);    // ���÷�������
    void randType();                                                            // �����������
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
    // �ƶ�������0 ��ʾ����һ��1 ��ʾ����һ��2 ��ʾ����һ�񣬵����Ƽ�⵽��ײʱ���� true
    bool move(const Dir& direction);
private:
    int m_x;                  // ���� X ����
    int m_y;                  // ���� Y ����
    int m_type;               // ��������
    int m_ind;
    const static int TYPE_NUM = 7;
    const static int BLOCK_DATA[TYPE_NUM][4];
    vector<int>& m_map;
public:
    const static COLORREF COLORS[TYPE_NUM];
};
