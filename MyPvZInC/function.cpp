#include "common.cpp"
void refresh() {
	{
		BeginBatchDraw();
		FlushBatchDraw();
		// 清屏
		cleardevice();
		// 绘制背景
		putimage(0, 0, &background);
		// 可能不需要绘制植物，能跑就别动
		PaintPeashooter();
		// 绘制僵尸
		for (int i = 1; i <= zombie_num; i++) {
			if (zombies[i-1].alive) {
				putimage(zombies[i - 1].x, y_line[zombies[i - 1].line] - 50, &zombie_img_white, SRCAND);
				putimage(zombies[i - 1].x, y_line[zombies[i - 1].line] - 50, &zombie_img_black, SRCPAINT);
				if_died(zombie_num);
			}
			if (gameover) {
				cleardevice();
			}
		}
		// 绘制子弹
		for (int i = 1; i <= bullet_num; i++) {
			if (bullets[i - 1].flag == 0) {
				putimage(bullets[i - 1].x, y_line[bullets[i - 1].line] + get_perfect_shoot_arg(bullets[i - 1].line), &bullet_img_white, SRCAND);
				putimage(bullets[i - 1].x, y_line[bullets[i - 1].line] + get_perfect_shoot_arg(bullets[i - 1].line), &bullet_img_black, SRCPAINT);
			}
			if (gameover) {
				cleardevice();
			}
		}
		EndBatchDraw();
	}
}

int get_remain_time(int start_time){
	return time(NULL) - start_time;
}

int place_zombie(Zombie zombies[], int zombie_num) {
	/* 初始化随机数发生器 */
	time_t t;
	srand((unsigned)time(&t));
	zombies[zombie_num-1].line = rand() % 5; // 生成0~4之间的随机数
	// 放置僵尸
	strcpy(zombies[zombie_num-1].name, "普通僵尸");
	zombies[zombie_num - 1].blood = 100;
	zombies[zombie_num - 1].x = 975;
	putimage(975, y_line[zombies[zombie_num - 1].line] - 50, &zombie_img_white, SRCAND);
	putimage(975, y_line[zombies[zombie_num - 1].line] - 50, &zombie_img_black, SRCPAINT);
	return 0;
}

int move_zombie(Zombie *zombie) {
	zombie->x -= 1;
	BeginBatchDraw();
	FlushBatchDraw();
	refresh();
	EndBatchDraw();
	return 0;
}

void LoadPeashooter(){
	for (int i = 0; i < 13; i++) {
		loadimage(&pea_shooter.image[0][i], pea_shooter_images_address_black[i]);//插入黑底彩图
		loadimage(&pea_shooter.image[1][i], pea_shooter_images_address_white[i]);//插入白底黑图
	}
}

void PaintPeashooter() 
{
	int i = pea_shooter.now_img_index;
	putimage(x[pea_shooter.position - 1], y[pea_shooter.position - 1], &pea_shooter.image[1][i],SRCAND);
	putimage(x[pea_shooter.position - 1], y[pea_shooter.position - 1], &pea_shooter.image[0][i],SRCPAINT);
}

void if_died(int zombie_num) {
	for (int i = 0; i < zombie_num; i++) {
		if (zombies[i].alive == 1) // 存活才判定
		{
			if (zombies[i].x < 50) {
				gameover = 1;
			}
			if (zombies[i].x <= x[pea_shooter.position - 1] - 10 && zombies[i].x >= x[pea_shooter.position - 1] - 120 && zombies[i].line == pea_shooter.line)
			{
				{
					gameover = 1;
				}
			}
		}
	}
}

int place_bullet(Bullet bullets[], int bullet_num) {

	bullets[bullet_num - 1].x = x[pea_shooter.position - 1] + 60;
	bullets[bullet_num - 1].line = pea_shooter.line;
	putimage(bullets[bullet_num -1].x, y_line[bullets[bullet_num - 1].line] + get_perfect_shoot_arg(bullets[bullet_num - 1].line), &bullet_img_white, SRCAND);
	putimage(bullets[bullet_num - 1].x, y_line[bullets[bullet_num - 1].line] + get_perfect_shoot_arg(bullets[bullet_num - 1].line), &bullet_img_black, SRCPAINT);
	return 0;
}

int move_bullet(Bullet* bullet) {
	bullet->x += 2;
	return 0;
}

int get_perfect_shoot_arg(int line) {
	switch (line) {
	case 1:
		return 20;
		break;
	case 2:
		return 10;
		break;
	case 3:
		return 20;
		break;
	case 4:
		return 15;
		break;
	case 0:
		return 10;
		break;
	}
}

// 绘制爱心函数
void heart(int x, int y, double scale) {
	setfillcolor(RED);
	solidrectangle((x - 35) * scale, y * scale, (x + 35) * scale, (y + 90) * scale);
	solidcircle((x - 45) * scale, y * scale, 55 * scale);
	solidcircle((x + 45) * scale, y * scale, 55 * scale);
	setlinecolor(COLORREF(BLACK));
	for (int i = 0; i <= 35; i++) {
		POINT pts1[] = { {(x - 70 - i * 1) * scale,(y - 50) * scale},
						 {(x - 140 - i * 1) * scale,y * scale},
						 {(x - 15 - i * 1) * scale,(y + 50) * scale},
						 {(x - i * 1) * scale,(y + 90) * scale}
		};
		POINT pts2[] = { {(x + 70 + i * 1) * scale,(y - 50) * scale},
						 {(x + 135 + i * 1) * scale,y * scale},
						 {(x + 17 + i * 1) * scale,(y + 50) * scale},
						 {(x + i * 1) * scale,(y + 90) * scale}
		};
		polybezier(pts1, 4);
		polybezier(pts2, 4);
	}
}