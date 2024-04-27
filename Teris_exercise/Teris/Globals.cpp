#include"Globals.h"
Configure* Configure::m_inst = NULL;
string Configure::m_fileName = "";

Configure::Configure() {
	ifstream reader(m_fileName.c_str(), ios::in);
	if (reader.is_open()) {
		//Read global variables from file 'config.txt'
		///////////////////////////////////////////////////
		// BEGIN OF YOUR CODE
		///////////////////////////////////////////////////



		///////////////////////////////////////////////////
		// END OF YOUR CODE
		///////////////////////////////////////////////////
	}
	else
		write();
	reader.close();
}
void Configure::write() {
	ofstream writter(m_fileName.c_str(), ios::out);
	writter << "MAP_WIDTH " << m_mapWidth << endl
		<< "MAP_HEIGHT " << m_mapHeight << endl
		<< "BLOCK_SIZE " << m_blockSize << endl
		<< "NEXT_BLOCK_NUM " << m_nextBlockNum << endl
		<< "MARGIN " << m_margin << endl
		<< "RIGHT_WD_RATIO " << m_rightWdRatio << endl
		<< "RIGHT_TXT_HT_RATIO " << m_rightTxtHtRatio << endl
		<< "RIGHT_BLK_HT_RATIO " << m_rightBlkHtRatio << endl
		<< "MAX_SCORE " << m_maxScore << endl;
	writter.close();
}