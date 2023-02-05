﻿#include "function.cpp"
int main()
{
	initgraph(800, 600);	// 创建绘图窗口，大小为 640x480 像素
	IMAGE start;
	loadimage(&start, L"./img/titlescreen.jpg");
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
	LoadKeyboardLayout(L"0x0409", KLF_ACTIVATE); // 设置英文键盘
	initgraph(1400, 600);
	loadimage(&zombie_img_black, L"./img/Zombieblack0.gif", 0, 0);
	loadimage(&zombie_img_white, L"./img/Zombiewhite0.gif");
	loadimage(&background, L"./img/background.jpg");
	loadimage(&bullet_img_white, L"./img/bulletwhite.gif", 0, 0);
	loadimage(&bullet_img_black, L"./img/bulletblack.gif", 0, 0);
	putimage(0, 0, &background);
	
	strcpy(pea_shooter.name, "pea_shooter");
	LoadPeashooter();
	// 初始位置
	pea_shooter.position = 2 * 9 + 1; //第三行第一个
	pea_shooter.line = 2;
	pea_shooter.blood = 100;
	PaintPeashooter();
	int timec_beginned = 0;
	while (1) {
		if (!timec_beginned) {
			_beginthread(timec_place_zombie, 0, NULL);
			_beginthread(timec_move_zombie, 0, NULL);
			_beginthread(timec_cartoon, 0, NULL);
			_beginthread(timec_refresh, 0, NULL);
			_beginthread(timec_place_bullet, 0, NULL);
			_beginthread(timec_move_bullet, 0, NULL);
			_beginthread(timec_check, 0, NULL);
			_beginthread(timec_rubbish_collect, 0, NULL);
			_beginthread(timec_bgm, 0, NULL);
			timec_beginned = 1;
		}
		// 从键盘获取移动的信息
		char key = _getch();
		if (key == 'w' || key == 'W') //W键
		{
			if (pea_shooter.position > 9) { // 不是第一行
				pea_shooter.position -= 9; // 上移一行
				pea_shooter.line -= 1;
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
				pea_shooter.line += 1;
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

void timec_place_zombie(void* pArg) {
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

void timec_cartoon(void*) {
	while (!gameover) {
		while (1){
			for (int i = 0; i < 13; i++) {
				Sleep(100);
				//0-12内循环
				pea_shooter.now_img_index = (pea_shooter.now_img_index + 1) % 13;
			}
		}
	} 
}

void timec_place_bullet(void*) {
	if (!gameover) {
		int have_shot = 0;
		while (1) {
			if (pea_shooter.now_img_index == 3 && have_shot == 0) {
				bullet_num++;
				int line = pea_shooter.line;
				bullets[bullet_num - 1].line = line;
				place_bullet(bullets, bullet_num);
				have_shot = 1;
			}
			else {
				have_shot = 0;
			}
			Sleep(50);
		}

	}
}

void timec_move_bullet(void*) {
	while (!gameover) {
		for (int i = 1; i <= bullet_num; i++) {
			move_bullet(&bullets[i - 1]);
		}
		Sleep(20);
	}
}

void timec_refresh(void *) {
	if (!gameover) {
		while (1){
			refresh();
			Sleep(50);
		}
	}
}

void timec_check(void*) {
	if (!gameover) {
		while (1) {
			// 检查子弹碰撞情况
			for (int i = 1; i <= bullet_num; i++) {
				for (int j = 1; j < zombie_num; j++) {
					if (bullets[i - 1].flag == 0 && zombies[j - 1].alive) {
						if (bullets[i - 1].line == zombies[j - 1].line && bullets[i - 1].x - 15 >= zombies[j - 1].x && bullets[i - 1].x - 20 <= zombies[j - 1].x) {
							bullets[i - 1].flag = 1;
							zombies[j - 1].blood -= 20;
							// 检查僵尸是否存活
							if (zombies[j - 1].blood <= 0) {
								zombies[j - 1].alive = 0;
							}
						}
					}
				}
			}
			Sleep(20);
		}
	}
}

void timec_rubbish_collect(void*) {
	while (1) {
		for (int i = 1; i <= zombie_num; i++) {
			if (zombies[i - 1].alive == 0) {
				// 删除已死亡的僵尸
				for (int j = i; j <= zombie_num; j++) {
					zombies[j - 1] = zombies[j];
				}
				zombie_num--;
			}
		}
		for (int i = 1; i <= bullet_num; i++) {
			if (bullets[i - 1].flag == 1 || bullets[i - 1].x > 1500) {
				// 删除已射中的子弹和超出边界的子弹
				for (int j = 1; j <= bullet_num; j++) {
					bullets[j - 1] = bullets[j];
				}
				bullet_num--;
			}
		}
		Sleep(20);
	}
}

void timec_bgm(void*) {
	while (1) {
		if (!gameover) {
			mciSendString(TEXT("open ./img/background_music.mp3 alias bgm"), NULL, 0, NULL);

			mciSendString(TEXT("play bgm"), NULL, 0, NULL);
			int s = 0;
			while (1) {
				if (s >= 300000) {  // 300秒后重新播放
					break;
				}
				Sleep(50); // 每50毫秒检查是否游戏结束
				s += 50;
				if (gameover) {
					mciSendString(TEXT("close bgm"), NULL, 0, NULL);
					_endthread();
				}
			}
		}
	}
}