#include "common.cpp"

int play(void);
int main()
{
	initgraph(800, 600);	// 创建绘图窗口，大小为 640x480 像素
	IMAGE start;
	loadimage(&start, L"F:\\MyPvZInC\\img\\titlescreen.jpg");
	putimage(0, 0, &start);
	ExMessage m;
	while (1) {
		m = getmessage(EX_MOUSE);
		switch (m.message) {
		case WM_LBUTTONDOWN:
			if (m.x > 330 && m.y > 439 && m.x < 514 && m.y < 496) {
				play();
			}
		}
	}
	_getch();				// 按任意键继续
	closegraph();			// 关闭绘图窗口
	return 0;
}

int play(void)
{
	initgraph(1100, 800);
	IMAGE background;
	loadimage(&background, L"F:\\MyPvZInC\\img\\background.jpg");
	putimage(0, 0, &background);
	Plant pea_shooter;
	strcpy(pea_shooter.name, "pea_shooter");
	strcpy(pea_shooter.image_path, "F:\\MyPvZInC\\img\\peashooter.png");
	pea_shooter.x = 262;
	pea_shooter.y = 285;
	pea_shooter.blood = 100;
	IMAGE pea_shooter_img;
	loadimage(&pea_shooter_img, L"F:\\MyPvZInC\\img\\peashooter.png");
	drawAlpha(&pea_shooter_img, pea_shooter.x, pea_shooter.y);
	return 0;
}
