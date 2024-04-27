#include "Game.h"
#include <easyx.h>
#include <ctime>
#include <iostream>
#include "enumerate.h"
using namespace std;
void Game::init() const {
    //HWND win = initgraph(TOTAL_WIDTH, TOTAL_HEIGHT, EX_SHOWCONSOLE);
    HWND win = initgraph(totalWidth(), totalHeight());
    SetWindowText(win, L"����˹����");

    // ������Ϸ���������
    srand((unsigned)time(NULL));

    // ���û�ͼ��ɫ
    setbkcolor(WHITE);
    cleardevice();
    setlinecolor(BLACK);

    // ���Ʊ߿�
    roundrect(MARGIN, MARGIN,
        windowWidth() + MARGIN, windowHeight() + MARGIN,
        MARGIN, MARGIN);
}
void Game::drawLeft() const {
    clearrectangle(leftXY(), leftXY(), leftXY() + leftWidth(), leftXY() + leftHeight());

    rectangle(2 * MARGIN, 2 * MARGIN,
        leftWidth() + 2 * MARGIN, leftHeight() + 2 * MARGIN);

    // Draw graphics according to 'map' variable.
    // NOTE: you should draw different colors for different
    //       type of block.
    ///////////////////////////////////////////////////
    // BEGIN OF YOUR CODE
    ///////////////////////////////////////////////////
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            int blockType = getMap(x, y);
            if (blockType != 0) { // �����ͼ�����λ���з���
                // ���ò�ͬ���͵ķ����Ӧ����ɫ
                COLORREF color;
                switch (blockType) {
                case 1: color = RED; break;
                case 2: color = GREEN; break;
                case 3: color = BLUE; break;
                case 4: color = YELLOW; break;
                case 5: color = CYAN; break;
                case 6: color = MAGENTA; break;
                case 7: color = LIGHTGRAY; break;
                default: color = BLACK; break;
                }
                // �����ɫ
                setfillcolor(color);
                // ���Ʒ���
                solidrectangle(leftXY() + x * BLOCK_SIZE, leftXY() + y * BLOCK_SIZE,
                    leftXY() + (x + 1) * BLOCK_SIZE - 1, leftXY() + (y + 1) * BLOCK_SIZE - 1);
            }
        }
    }

    ///////////////////////////////////////////////////
    // END OF YOUR CODE
    ///////////////////////////////////////////////////
    m_curBlk.draw(leftXY(), leftXY());
}

void Game::drawRight() const {

    clearrectangle(rightX(), rightY(), rightX() + rightWidth(), rightY() + leftHeight());

    rectangle(rightX(), rightTxtHeight() + 2 * MARGIN,
        rightX() + rightWidth(), rightTxtHeight() + 2 * MARGIN + rightBlkHeight());
    // ��������
    int txt_y = rightY();
    int txt_step = rightTxtHeight() / 4;
    LOGFONT f;
    gettextstyle(&f);
    f.lfHeight = long(txt_step * 0.8);
    wcscpy_s(f.lfFaceName, L"΢���ź�");
    f.lfQuality = DEFAULT_QUALITY;
    settextstyle(&f);
    settextcolor(BLACK);


    // ���� �������� �� ��ʱ�䡱
    wchar_t str[10];

    wsprintf(str, L"S: %u", score);
    outtextxy(rightX(), txt_y, str);
    txt_y += txt_step;

    wsprintf(str, L"T: %us", gameTime / 1000);
    outtextxy(rightX(), txt_y, str);
    txt_y += txt_step;

    int maxScore = Configure::getInst()->maxScore();
    wsprintf(str, L"M: %i", maxScore);
    outtextxy(rightX(), txt_y, str);
    txt_y += txt_step;

    // ���� ����һ���顱 ��ʾ
    outtextxy(rightX(), txt_y, L"Seq.");
    txt_y += txt_step;

    drawNextBlks();
}

bool Game::checkLine(const unsigned& line) const {
    for (int i = 0; i < MAP_WIDTH; i++) {
        if (getMap(i, line) == 0) {
            return false;
        }
    }
    return true;
}

void Game::clearLine() {
    //Rewrite this function, implement the following logic:
    // If (there are 1 line to clear)
    //     score += 10
    // Else if (there are 2 lines to clear)
    //     score += 30
    // Else if (there are 3 lines to clear)
    //     score += 50
    // Else if (there are 4 lines to clear)
    //     score += 70
    // NOTE: When you done this logic, please comment out 
    //      the code after "END OF YOUR CODE"

    ///////////////////////////////////////////////////
    // BEGIN OF YOUR CODE
    ///////////////////////////////////////////////////
    int linesCleared = 0;
    for (int j = 0; j < MAP_HEIGHT; j++) {
        if (checkLine(j)) {

            for (int k = j; k > 0; k--) {
                for (int i = 0; i < MAP_WIDTH; i++) {
                    setMap(i, k, getMap(i, k - 1));
                }
            }

            for (int i = 0; i < MAP_WIDTH; i++) {
                setMap(i, 0, 0);
            }
            linesCleared++;
        }
    }

    switch (linesCleared) {
    case 1: score += 10; break;
    case 2: score += 30; break;
    case 3: score += 50; break;
    case 4: score += 70; break;
    }

    ///////////////////////////////////////////////////
    // END OF YOUR CODE
    ///////////////////////////////////////////////////

    
    
  
}
void Game::addBlkToMap() {
    int bx, by;
    for (int i = 0; i < 4; i++) {
        bx = m_curBlk.getX(i);
        by = m_curBlk.getY(i);
        setMap(m_curBlk.x() + bx, m_curBlk.y() + by, m_curBlk.type());
    }
}
void Game::genNewBlks() {

    //Generate new blocks, 
    // 
    ///////////////////////////////////////////////////
    // BEGIN OF YOUR CODE
    ///////////////////////////////////////////////////
    if (m_nextBlks.empty()) {
        
        
        }
    else {

    }
    ///////////////////////////////////////////////////
    // END OF YOUR CODE
    ///////////////////////////////////////////////////
    m_curBlk.setPos();

    int x = MAP_WIDTH + 1;
    int y = rightTxtHeight() / BLOCK_SIZE + 1;
    for (auto blk : enumerate(m_nextBlks))
        blk.item.setPos(x, y + 4 * int(blk.index));
    }
}
void Game::drawNextBlks() const {
    // Draw all the elements in m_nextBlks
    ///////////////////////////////////////////////////
    // BEGIN OF YOUR CODE
    ///////////////////////////////////////////////////
    int x = rightX() + MARGIN;
    int y = rightTxtHeight() + 3 * MARGIN;
    for (const Block& blk : m_nextBlks)
        blk.draw(x, y);
    ///////////////////////////////////////////////////
    // END OF YOUR CODE
    ///////////////////////////////////////////////////
};
bool Game::processKeyDown() {
    ExMessage msg;
    // ��������
    if (peekmessage(&msg, EX_KEY) && msg.message == WM_KEYDOWN) {
        switch (msg.vkcode) {

        case 'W': case VK_UP:// �ϼ���ת
            m_curBlk.rotate();
            break;
        case 'S': case VK_DOWN:// �¼���������
            while (!m_curBlk.moveDown());
            addBlkToMap();
            genNewBlks();
            drawNextBlks();
            // �������ո�����ȴ��������ײ��˵����Ϸ����
            if (m_curBlk.checkCollision()) {
                MessageBox(GetHWnd(), L"��Ϸ������", L"��ʾ", MB_ICONWARNING);
                return true;
            }
            break;
        case 'A': case VK_LEFT:// ����ƶ�
            m_curBlk.moveLeft();
            break;
        case 'D': case VK_RIGHT:// �Ҽ��ƶ�
            m_curBlk.moveRight();
            break;
        case 'Q': case VK_ESCAPE:// Esc ���˳�����
            return true;
        }
    }
    return false;
}
bool Game::updateBlk() {
    static clock_t start = 0, end; // ʱ�ӿ�ʼʱ��
    end = clock();
    if (end - start >= 500) {
        if (m_curBlk.moveDown()) {
            // �������÷���
            addBlkToMap();
            genNewBlks();

            // �������ո�����ȴ��������ײ��˵����Ϸ����
            if (m_curBlk.checkCollision()) {
                MessageBox(GetHWnd(), L"��Ϸ������", L"��ʾ", MB_ICONWARNING);
                return true;
            }
        }
        start = clock();
        addGameTime();
    }
    clearLine();
    return false;
}
void Game::loop() {
    BeginBatchDraw();
    while (true) {
        drawLeft();
        drawRight();

        if (processKeyDown())
            break;
        if (updateBlk())     // ÿ���� 500 ���뷽������һ��
            break;
        FlushBatchDraw();    // ˢ�»�����
        Sleep(50);           // ÿ 50 �������һ�ΰ���
    }
    EndBatchDraw();
}
void Game::writeMaxScore() {
    //Write max score to file, using class Configure::write
    // 
    ///////////////////////////////////////////////////
    // BEGIN OF YOUR CODE
    ///////////////////////////////////////////////////
    Configure::getInst()->write();
    ///////////////////////////////////////////////////
    // END OF YOUR CODE
    ///////////////////////////////////////////////////
}