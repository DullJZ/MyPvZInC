#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
#include <Windows.h>
int play(void);
int main()
{
	initgraph(800, 600);	// 创建绘图窗口，大小为 640x480 像素
	IMAGE start;
	loadimage(&start, L"F:\\MyPvZInC\\titlescreen.jpg");
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
	MessageBox(NULL, L"游戏界面",L"Play",MB_OK);
	return 0;
}
