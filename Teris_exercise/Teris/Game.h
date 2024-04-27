#pragma once
#include "Globals.h"
#include "Block.h"
#include <list>
#include<iostream>
#include <vector>
#include "my_list.h"
using namespace std;
// 游戏类
class Game
{
public:
    Game() :m_curBlk(map) {
        map.resize(MAP_WIDTH * MAP_HEIGHT);
        genNewBlks();
    }
    ~Game() {
        closegraph();
    }
    void init() const;
    void drawLeft() const;                      // 绘制地图
    void drawRight() const;                     // 绘制提示界面

    bool checkLine(const unsigned& line) const;  // 判断满行
    void clearLine();                            // 清除满行
    bool processKeyDown();
    bool updateBlk();
    void writeMaxScore();
    void loop();
public:
    // 设置地图
    void setMap(const int& x, const int& y, const int& value) {
        map[y * MAP_WIDTH + x] = value;
    }

    // 获取地图
    const int& getMap(const int& x, const int& y) const {
        return map[y * MAP_WIDTH + x];
    }

    // 添加游戏时间
    void addGameTime() {
        gameTime += 500;
    }
private:
    int leftWidth() const { return MAP_WIDTH * BLOCK_SIZE; }
    int leftHeight() const { return MAP_HEIGHT * BLOCK_SIZE; }
    int leftXY() const { return 2 * MARGIN; }

    int rightWidth() const { return int(RIGHT_WIDTH_RATIO * leftWidth()); }
    int rightTxtHeight() const { return int(RIGHT_TXT_HT_RATIO * leftHeight()); }
    int rightBlkHeight() const { return int(RIGHT_BLK_HT_RATIO * leftHeight()); }
    int windowWidth() const { return leftWidth() + rightWidth() + 3 * MARGIN; }
    int windowHeight() const { return MARGIN + leftHeight() + MARGIN; }
    int totalWidth() const { return windowWidth() + 2 * MARGIN; }
    int totalHeight() const { return windowHeight() + 2 * MARGIN; }
    int rightX() const { return leftXY() + leftWidth() + MARGIN; }
    int rightY() const { return leftXY(); }

    void genNewBlks();
    void addBlkToMap();
    void drawNextBlks() const;
private:
    vector<int> map;    // 地图数组
    int score = 0;                        // 游戏分数
    unsigned gameTime = 0;                     // 游戏时间
    Block m_curBlk;

    // You can modify m_nextBlks to type list<Block> if you want
    // to do homework2 before accomplishing homework1, since 'list'
    // is a STL container already implemented by your compiler.
    my_list<Block> m_nextBlks;
};