#include <iostream>
#include "Sence.h"

using namespace std;

// int row, col, boomNum;
// Sence* sence;

int main() {
	int row, col, boomNum;
	cout << "����һ��ɨ����Ϸ���붨���С���׵�������" << endl;
	cout << "�У�";		cin >> row;
	cout << "�У�";		cin >> col;
	cout << "�׵�������";	cin >> boomNum;
	
	initgraph(col * GridSize, row * GridSize + row * 6);
	setbkcolor(RGB(224, 224, 224));
	cleardevice();

	Sence* sence = new Sence;
	// sence = new Sence;

	sence->Init(row, col, boomNum);
	sence->PlayGame();

	delete sence;

	return 0;
}




// int main() {
//	// �зֻ�ȡ����ͼƬ

//	initgraph(83 * 12, 83);
//	IMAGE* m = new IMAGE;
//	loadimage(m, "res/image/total.png");
//	putimage(0, 0, m);

//	IMAGE* get_m = new IMAGE[12];
//	for (int i = 0; i < 12; i++) {
//		getimage(&get_m[i], 1 + i * 78, 4, 78, 78);
//	}


//	for (int i = 0; i < 12; i++) {
//		char str[100] = { 0 };
//		sprintf_s(str, sizeof(str), "res/image/%d.png", i);

//		saveimage(str, &get_m[i]);
//	}

//	// getchar();
 
//	// delete[] get_m;
//	// delete m;
 
//	return 0;
// }

// int main() {
//	// �зֻ�ȡredboomͼƬ

//	initgraph(100, 100);
//	IMAGE* m = new IMAGE;
//	loadimage(m, "res/image/redboom.png", GridSize, GridSize + 1);
//	putimage(0, 0, m);

//	IMAGE* get_m = new IMAGE;
//	getimage(get_m, 0, 0, GridSize, GridSize);

//	saveimage("res/image/-2.png", get_m);

//	// getchar();
//	return 0;
// }