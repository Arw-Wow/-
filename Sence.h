#pragma once

#include <time.h>
#include <cstdlib>
#include <easyx.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#define BOOM -1
#define REDBOOM -2
#define HIDE 10
#define FLAG 11
#define GridSize 39

class Sence
{
public:
	Sence() = default;
	void Init(int _row, int _col, int _boomNum);
	void PlayGame();
	void test();	// �ڿ���̨���ÿ�����ӵ�����
	// void EndGame();

private:
	void caculate();
	void InitImage();
	void displayText();
	// void removeText();
	void displayTime();
	void InitBoard();
	void setImage(int x, int y, int type);
	bool findPosition_and_setImage_and_checkBoom(ExMessage msg);
	void findPosition_and_setFlag(ExMessage msg);
	int getLeftBoomNum();	// ���ݲ�����������ʣ����������������ʣ�������
	bool checkBoom(int type);
	void openSuround(int curRow, int curCol);
	void LoseGame(int curRow, int curCol);	// ��Ҫ�����һ�ε������Ϊ��ɫ���ף�����Ҫ���뵱ǰ���λ��
	void WinGame();
	bool Check_if_win();

private:
	int** board;
	bool** HideBoard;	// ���ڴ洢�Ƿ��Ѿ��򿪣������ظ���
	bool** FlagBoard;	// ���ڴ洢�Ƿ��Ѿ����죬�����ظ�����
	int row;
	int col;
	int boomNum; //ը������
	// int boomLeftNum;	//ʣ��ը������
};

