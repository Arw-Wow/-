#include "Sence.h"

void Sence::Init(int _row, int _col, int _boomNum)
{
	srand(time(0));

	row = _row;
	col = _col;
	boomNum = _boomNum >= row * col ? row * col - 1 : _boomNum;

	board = new int* [row];
	for (int i = 0; i < row; i++) {
		board[i] = new int[col];
	}

	HideBoard = new bool* [row];
	for (int i = 0; i < row; i++) {
		HideBoard[i] = new bool[col];
	}
	
	FlagBoard = new bool* [row];
	for (int i = 0; i < row; i++) {
		FlagBoard[i] = new bool[col];
	}

	int i = boomNum;
	while (i) {	//������� boomNum ��ը��
		int r = rand() % row;
		int l = rand() % col;
		if (board[r][l] == BOOM)
			continue;
		board[r][l] = BOOM; //BOOM Ϊ -1
		--i;
	}

	caculate();	//���ɸ�����������

	InitImage();	//����ͼ��
	InitBoard();	//��ʼ��HideBoard��FlagBoard
	displayText();
}

void Sence::PlayGame()
{
	ExMessage msg;
	while (1) {
		displayTime();

		if (peekmessage(&msg, EX_MOUSE)) {	// �õ���Ϣ�ʹ���û�õ���Ϣ��һֱѭ������������
			if (msg.message == WM_LBUTTONDOWN) {
				if (findPosition_and_setImage_and_checkBoom(msg))
					return;
				// test();
				// displayText();
			}

			else if (msg.message == WM_RBUTTONDOWN) {
				findPosition_and_setFlag(msg);
				displayText();
			}


			if (Check_if_win()) {
				WinGame();
				return;
			}
		}
	}
}

void Sence::test()
{
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << board[i][j] << '\t';
		}
		cout << endl;
	}
	cout << endl;
}

void Sence::caculate()
{
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (board[i][j] == BOOM)	continue;	//����ը������

			// ��ÿһ���㣬ȷ����Χ�˸������Ƿ���ը��
			int boomNum_point = 0;
			
			//�˸�����
			for (int x = -1; x <= 1; x++) {
				for (int y = -1; y <= 1; y++) {
					// �Լ��Ǹ��������Ҳû��ϵ����������ը��
					// board[i + y][j + x]
					if (i + y < 0 || i + y >= row || j + x < 0 || j + x >= col)
						continue;	// �����߽������

					if (board[i + y][j + x] == BOOM) {
						boomNum_point++;

					}
				}
			}
			board[i][j] = boomNum_point;
		}
	}
}

void Sence::InitImage()
{
	IMAGE* m = new IMAGE;
	loadimage(m, "res/image/10.png");
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			putimage(j * GridSize, i * GridSize, m);
		}
	}
	delete m;
}

void Sence::displayText()
{
	static char str[25] = { 0 };	//��static��Ϊ�˴洢��һ�����������
	// char str[25] = { 0 };

	settextcolor(getbkcolor());	//����������Ϊ����ɫ�������һ�飬����������һ�ε����֣�
	outtextxy(col * GridSize - 130, row * GridSize + 10, str);

	settextcolor(BLACK);
	sprintf_s(str, sizeof(str), "��ʣ %d ����", getLeftBoomNum());
	outtextxy(col * GridSize - 130, row * GridSize + 10, str);
}

void Sence::displayTime()
{
	static time_t beginTime = clock();
	time_t curTime = clock();

	static char str[25] = { 0 };

	// settextcolor(getbkcolor());	//����������Ϊ����ɫ�������һ�飬����������һ�ε����֣�
	// outtextxy(30, row * GridSize + 10, str);

	settextcolor(BLACK);
	sprintf_s(str, sizeof(str), "��ʱ��%d", (int)(curTime - beginTime) / 1000);
	outtextxy(30, row * GridSize + 10, str);
}

void Sence::InitBoard()
{
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			HideBoard[i][j] = true;
			FlagBoard[i][j] = false;
		}
	}
}

void Sence::setImage(int x, int y, int type)
{
	IMAGE m;
	char filename[100] = { 0 };
	sprintf_s(filename, "res/image/%d.png", type);
	loadimage(&m, filename);
	putimage(x, y, &m);

	int curRow = y / GridSize;
	int curCol = x / GridSize;

	if (type != HIDE && type != FLAG) {
		HideBoard[curRow][curCol] = false;
		FlagBoard[curRow][curCol] = false;
	}
	if (type == HIDE) {
		HideBoard[curRow][curCol] = true;
		FlagBoard[curRow][curCol] = false;
	}
	if (type == FLAG) {
		HideBoard[curRow][curCol] = true;
		FlagBoard[curRow][curCol] = true;
	}

	// static int i = 0;
	// cout << i++ << endl;

}

bool Sence::findPosition_and_setImage_and_checkBoom(ExMessage msg)
{
	for (int curRow = 0; curRow < row; curRow++) {
		for (int curCol = 0; curCol < col; curCol++) {
			int x = curCol * GridSize;
			int y = curRow * GridSize;
			if (msg.x > x && msg.x < x + GridSize && msg.y > y && msg.y < y + GridSize && FlagBoard[curRow][curCol] == false) {
				int type = board[curRow][curCol];
				setImage(x, y, type);
				if (type == 0) {
					openSuround(curRow, curCol);
				}
				if (checkBoom(type)) {
					LoseGame(curRow, curCol);
					return true;
				}
				return false;
			}
		}
	}
	return false;
}

void Sence::findPosition_and_setFlag(ExMessage msg)
{
	for (int curRow = 0; curRow < row; curRow++) {
		for (int curCol = 0; curCol < col; curCol++) {
			int x = curCol * GridSize;
			int y = curRow * GridSize;
			if (msg.x > x && msg.x < x + GridSize && msg.y > y && msg.y < y + GridSize && HideBoard[curRow][curCol] == true) {
				if (FlagBoard[curRow][curCol] == false) {
					setImage(x, y, FLAG);
				}
				else {
					setImage(x, y, HIDE);
				}
				return;
			}
		}
	}
}

int Sence::getLeftBoomNum()
{
	int flagNum = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (FlagBoard[i][j] == true)
				flagNum++;
		}
	}
	return boomNum - flagNum >= 0 ? boomNum - flagNum : 0;
}

bool Sence::checkBoom(int type)
{
	if (type != BOOM)
		return false;

	return true;
}

void Sence::openSuround(int curRow, int curCol)
{
	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			if (x == 0 && y == 0)	continue;	// �Լ����������
			if (curRow + y < 0 || curRow + y >= row || curCol + x < 0 || curCol + x >= col)
						continue;	// �����߽������
			if (board[curRow + y][curCol + x] == BOOM)	continue;	//��ʵ����һƬ�հ׵�ʱ�򣬲�����������ը����һ�������������֡�����������һ��
			if (HideBoard[curRow + y][curCol + x] == false)	continue;	// ����Ѿ������ˣ��Ͳ��ٴ�
			if (FlagBoard[curRow + y][curCol + x] == true)	continue;	// ����Ѿ������ˣ��Ͳ��ٴ�

			int type = board[curRow + y][curCol + x];
			setImage((curCol + x) * GridSize, (curRow + y) * GridSize, type);

			if (type == 0) {
				openSuround(curRow + y, curCol + x);
			}
		}
	}
}

void Sence::LoseGame(int curRow, int curCol)
{
	// ȫ��ʾ�汾
	// for (int i = 0; i < row; i++) {
	//	for (int j = 0; j < col; j++) {
	//		setImage(j * GridSize, i * GridSize, board[i][j]);
	//	}
	// }

	// ֻ��ʾ�װ汾
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (board[i][j] == BOOM)
				setImage(j * GridSize, i * GridSize, BOOM);
		}
	}

	setImage(curCol * GridSize, curRow * GridSize, REDBOOM);

	MessageBox(NULL, "��ȵ����ˣ�", "��Ϸ����", MB_OKCANCEL);
}

void Sence::WinGame()
{
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (board[i][j] == BOOM)
				setImage(j * GridSize, i * GridSize, FLAG);
		}
	}

	MessageBox(NULL, "��ɹ��ҵ������е��ף�", "��Ϸ����", MB_OKCANCEL);
}

bool Sence::Check_if_win()
{
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (board[i][j] != BOOM && HideBoard[i][j] == true)
				return false;
		}
	}
	return true;
}


