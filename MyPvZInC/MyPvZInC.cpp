﻿#include "function.cpp"
int main()
{
	initgraph(800, 600);	// 创建绘图窗口，大小为 640x480 像素
	IMAGE start;
	loadimage(&start, L".\\img\\titlescreen.jpg");
	putimage(0, 0, &start);
	ExMessage m;
	int start_time = 0;
	while (1) {
		m = getmessage(EX_MOUSE);
		switch (m.message) {
		case WM_LBUTTONDOWN:
			if (m.x > 330 && m.y > 439 && m.x < 514 && m.y < 496) {
				start_time = time(NULL);
				play();
			}
		}
	}
	closegraph();			// 关闭绘图窗口
	return 0;
}

int play()
{
	initgraph(1400, 600);
	loadimage(&zombie_img_black, L"./img/Zombieblack0.gif", 0, 0);
	loadimage(&zombie_img_white, L"./img/Zombiewhite0.gif");
	loadimage(&background, L".\\img\\background.jpg");
	putimage(0, 0, &background);
	
	strcpy(pea_shooter.name, "pea_shooter");
	LoadPeashooter(pea_shooter.image);
	// 初始位置
	pea_shooter.position = 2 * 9 + 1; //第三行第一个
	pea_shooter.blood = 100;
	PaintPeashooter();
	int timec_beginned = 0;
	while (1) {
		if (!timec_beginned) {
			_beginthread(timec_place_zombie, 0, NULL);
			_beginthread(timec_move_zombie, 0, NULL);
			timec_beginned = 1;
		}
		// 从键盘获取移动的信息
		char key = _getch();
		if (key == 'w' || key == 'W') //W键
		{
			if (pea_shooter.position > 9) { // 不是第一行
				pea_shooter.position -= 9; // 上移一行
				refresh();
			}
		}
		if (key == 'a' || key == 'A') //A键
		{
			if (pea_shooter.position % 9 != 1) { // 不是第一列
				pea_shooter.position -= 1; // 左移一列
				refresh();
			}
		}
		if (key == 's' || key == 'S') //S键
		{
			if (pea_shooter.position <= 36) { // 不是第五行
				pea_shooter.position += 9; // 下移一行
				refresh();
			}
		}
		if (key == 'd' || key == 'D') //D键
		{
			if (pea_shooter.position % 9 != 0) { // 不是第九列
				pea_shooter.position += 1; // 右移一列
				refresh();
			}
		}

	}
	return 0;
}

void timec_place_zombie(void*) {
	int start_time = time(NULL);
	while (!gameover) {
		int s = time(NULL) - start_time;
		if (s!=0 && s%5==0) {
			zombie_num++;
			place_zombie(zombies, zombie_num);
			
			
		}
		Sleep(1000);
	}
}

void timec_move_zombie(void*) {
	Sleep(6000);
	while (!gameover) {
		for (int i = 1; i <= zombie_num; i++) {
			move_zombie(&zombies[i - 1]);
		}
		Sleep(20);
	}
}