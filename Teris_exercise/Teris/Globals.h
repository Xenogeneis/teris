#pragma once
#include<string>
#include<fstream>
using namespace std;

#define MAP_WIDTH (Configure::getInst()->mapWidth())
#define MAP_HEIGHT (Configure::getInst()->mapHeight())
#define BLOCK_SIZE (Configure::getInst()->blockSize())
#define NEXT_BLOCK_NUM (Configure::getInst()->nextBlockNum())
#define MARGIN (Configure::getInst()->margin())
#define RIGHT_WIDTH_RATIO (Configure::getInst()->rightWdRatio())
#define RIGHT_TXT_HT_RATIO (Configure::getInst()->rightTxtHtRatio())
#define RIGHT_BLK_HT_RATIO (Configure::getInst()->rightBlkHtRatio())
#define MAX_SCORE (Configure::getInst()->maxScore())

class Configure {
private:
	static string m_fileName;
	static Configure* m_inst;

	int m_mapWidth = 10;
	int m_mapHeight = 20;
	int m_blockSize = 20;
	int m_nextBlockNum = 3;
	int m_margin = 10;
	float m_rightWdRatio = 0.5f;
	float m_rightTxtHtRatio = 0.3f;
	float m_rightBlkHtRatio = 0.7f;
	int m_maxScore = 0;

	Configure();
public:
	static void init(string fName) {
		m_fileName = fName;
		m_inst = getInst();
	}
	static Configure* getInst() {
		return m_inst ? m_inst : new Configure();
	}
	void write();

	int mapWidth() { return m_mapWidth; }
	int mapHeight() { return m_mapHeight; }
	int blockSize() { return m_blockSize; }
	int nextBlockNum() { return m_nextBlockNum; }
	int margin() { return m_margin; }
	float rightWdRatio() { return m_rightWdRatio; }
	float rightTxtHtRatio() { return m_rightTxtHtRatio; }
	float rightBlkHtRatio() { return m_rightBlkHtRatio; }
	int maxScore() { return m_maxScore; }
	void setMaxScore(int m) { m_maxScore = m; }
};