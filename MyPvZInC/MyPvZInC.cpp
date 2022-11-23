#include "function.cpp"
int play(void);
int main()
{
	initgraph(800, 600);	// 创建绘图窗口，大小为 640x480 像素
	IMAGE start;
	loadimage(&start, L".\\img\\titlescreen.jpg");
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
	closegraph();			// 关闭绘图窗口
	return 0;
}

int play(void)
{
	initgraph(1100, 800);
	IMAGE background;
	loadimage(&background, L".\\img\\background.jpg");
	putimage(0, 0, &background);
	Plant pea_shooter;
	strcpy(pea_shooter.name, "pea_shooter");
	strcpy(pea_shooter.image_path, ".\\img\\Peashooter.gif");
	// 初始位置
	pea_shooter.position = 2 * 9 + 1; //第三行第一个
	pea_shooter.blood = 100;
	IMAGE pea_shooter_img;
	loadimage(&pea_shooter_img, L".\\img\\Peashooter.gif");
	//暂时不考虑透明贴图问题和GIF动画问题
	putimage(x[pea_shooter.position-1], y[pea_shooter.position-1], &pea_shooter_img);
	//drawAlpha(&pea_shooter_img, pea_shooter.x, pea_shooter.y,);
	while (1) {
		char key = _getch();
		if (key == 'w' || key == 'W') //W键
		{
			if (pea_shooter.position > 9) { // 不是第一行
				clear(background);
				pea_shooter.position -= 9; // 上移一行
				putimage(x[pea_shooter.position - 1], y[pea_shooter.position-1], &pea_shooter_img);
			}
		}
		if (key == 'a' || key == 'A') //A键
		{
			if (pea_shooter.position % 9 != 1) { // 不是第一列
				clear(background);
				pea_shooter.position -= 1; // 左移一列
				putimage(x[pea_shooter.position - 1], y[pea_shooter.position-1], &pea_shooter_img);
			}
		}
		if (key == 's' || key == 'S') //S键
		{
			if (pea_shooter.position <= 36) { // 不是第五行
				clear(background);
				pea_shooter.position += 9; // 下移一行
				putimage(x[pea_shooter.position - 1], y[pea_shooter.position-1], &pea_shooter_img);
			}
		}
		if (key == 'd' || key == 'D') //D键
		{
			if (pea_shooter.position % 9 != 0) { // 不是第九列
				clear(background);
				pea_shooter.position += 1; // 右移一列
				putimage(x[pea_shooter.position - 1], y[pea_shooter.position-1], &pea_shooter_img);
			}
		}
	}
	return 0;
}

