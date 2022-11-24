#include "function.cpp"
int play(int);
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
				play(start_time);
			}
		}
	}
	closegraph();			// 关闭绘图窗口
	return 0;
}

int play(int start_time)
{
	initgraph(1100, 800);
	IMAGE background;
	loadimage(&background, L".\\img\\background.jpg");
	putimage(0, 0, &background);
	Plant pea_shooter;
	strcpy(pea_shooter.name, "pea_shooter");
	loadimage(&pea_shooter.image,L".\\img\\Peashooter.gif");
	Zombie zombies[100];
	Timer timer;
	timer.start_time = start_time;
	// 初始位置
	pea_shooter.position = 2 * 9 + 1; //第三行第一个
	pea_shooter.blood = 100;
	//暂时不考虑透明贴图问题和GIF动画问题
	putimage(x[pea_shooter.position-1], y[pea_shooter.position-1], &pea_shooter.image);
	//drawAlpha(&pea_shooter.image, pea_shooter.x, pea_shooter.y,);
	while (1) {
		// 更新计时器
		int s = time(NULL) - timer.start_time;
		int seconds = s % 60 % 60;
		int minites = (s - seconds) % 60;
		int hours = (s - seconds - minites * 60) / 3600;
		_stprintf(timer.str, _T("%d:%d:%d"), hours, minites, seconds);
		outtextxy(timer.x, timer.y, timer.str);
		// 从键盘获取移动的信息
		char key = _getch();
		if (key == 'w' || key == 'W') //W键
		{
			if (pea_shooter.position > 9) { // 不是第一行
				fresh(background,pea_shooter,zombies);
				pea_shooter.position -= 9; // 上移一行
				putimage(x[pea_shooter.position - 1], y[pea_shooter.position-1], &pea_shooter.image);
			}
		}
		if (key == 'a' || key == 'A') //A键
		{
			if (pea_shooter.position % 9 != 1) { // 不是第一列
				fresh(background, pea_shooter, zombies);
				pea_shooter.position -= 1; // 左移一列
				putimage(x[pea_shooter.position - 1], y[pea_shooter.position-1], &pea_shooter.image);
			}
		}
		if (key == 's' || key == 'S') //S键
		{
			if (pea_shooter.position <= 36) { // 不是第五行
				fresh(background, pea_shooter, zombies);
				pea_shooter.position += 9; // 下移一行
				putimage(x[pea_shooter.position - 1], y[pea_shooter.position-1], &pea_shooter.image);
			}
		}
		if (key == 'd' || key == 'D') //D键
		{
			if (pea_shooter.position % 9 != 0) { // 不是第九列
				fresh(background, pea_shooter, zombies);
				pea_shooter.position += 1; // 右移一列
				putimage(x[pea_shooter.position - 1], y[pea_shooter.position-1], &pea_shooter.image);
			}
		}

	}
	return 0;
}

