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
				if (bullets[i - 1].type == 1) {
					putimage(bullets[i - 1].x, y_line[bullets[i - 1].line] + get_perfect_shoot_arg(bullets[i - 1].line), &bullet_img_white, SRCAND);
					putimage(bullets[i - 1].x, y_line[bullets[i - 1].line] + get_perfect_shoot_arg(bullets[i - 1].line), &bullet_img_black, SRCPAINT);
				}
				else {
					putimage(bullets[i - 1].x, y_line[bullets[i - 1].line] + get_perfect_shoot_arg(bullets[i - 1].line), &superbullet_img_white, SRCAND);
					putimage(bullets[i - 1].x, y_line[bullets[i - 1].line] + get_perfect_shoot_arg(bullets[i - 1].line), &superbullet_img_black, SRCPAINT);
				}
			}
			if (gameover) {
				cleardevice();
			}
		}
		// 绘制技能
		if (fire_available){
			putimage(0, 500, &fire_img_white, SRCAND);
			putimage(0, 500, &fire_img_black, SRCPAINT);
		}
		else {
			putimage(0, 500, &grayfire_img_white, SRCAND);
			putimage(0, 500, &grayfire_img_black, SRCPAINT);
		}
		EndBatchDraw();
	}
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

int place_superbullet(Bullet bullets[], int bullet_num) {
	bullets[bullet_num - 1].x = x[pea_shooter.position - 1] + 60;
	bullets[bullet_num - 1].line = pea_shooter.line;
	bullets[bullet_num - 1].hurt = 100;
	bullets[bullet_num - 1].type = 2;
	putimage(bullets[bullet_num - 1].x, y_line[bullets[bullet_num - 1].line] + get_perfect_shoot_arg(bullets[bullet_num - 1].line), &superbullet_img_white, SRCAND);
	putimage(bullets[bullet_num - 1].x, y_line[bullets[bullet_num - 1].line] + get_perfect_shoot_arg(bullets[bullet_num - 1].line), &superbullet_img_black, SRCPAINT);
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


// 给排行榜排序，返回最高分
int sort() {
	FILE* fp;
	fp = fopen("./list.txt", "r+");
	int list[100] = { 0 };
	int i = 0, t = 0;
	char ch = 0;
	if (fp != NULL) {
		// 读入数据
		while (fscanf(fp,"%d\n",&list[i]) != EOF) {
			i++;
		}
		// 开始排序
		for (int a = 0; a < i; a++) {
			for (int b = a; b < i; b++) {
				if (list[a] < list[b]) {
					int tmp = list[a];
					list[a] = list[b];
					list[b] = tmp;
				}
			}
		}
		// 重新输出
		rewind(fp);
		for (int a = 0; a < i; a++) {
			fprintf(fp, "%d\n", list[a]);
		}
		fclose(fp);
		return list[0];
	}
	
}