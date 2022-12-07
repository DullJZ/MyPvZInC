#include "common.cpp"
void PaintPeashooter();
void refresh() {
	{
		// ����
		cleardevice();
		// ���Ʊ���
		putimage(0, 0, &background);
		// ����ֲ��
		PaintPeashooter();
		// ���ƽ�ʬ
		for (int i = 1; i <= zombie_num; i++) {
			putimage(zombies[i - 1].x, y_line[zombies[i - 1].line] - 50, &zombie_img_white, SRCAND);
			putimage(zombies[i - 1].x, y_line[zombies[i - 1].line] - 50, &zombie_img_black, SRCPAINT);
			if_died(zombie_num);
			if (gameover) {
				cleardevice();
			}
		}
		
	}
}

int get_remain_time(int start_time){
	return time(NULL) - start_time;
}

int place_zombie(Zombie zombies[], int zombie_num) {
	/* ��ʼ������������� */
	time_t t;
	srand((unsigned)time(&t));
	zombies[zombie_num-1].line = rand() % 5; // ����0~5֮��������
	// ���ý�ʬ
	strcpy(zombies[zombie_num-1].name, "��ͨ��ʬ");
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

void LoadPeashooter(IMAGE Peashooter[2][13])
{
	loadimage(&Peashooter[0][0], pea_shooter_images_address_black[0]);//����ڵײ�ͼ
	loadimage(&Peashooter[1][0], pea_shooter_images_address_white[0]);//����׵׺�ͼ
}

void PaintPeashooter() 
{
	putimage(x[pea_shooter.position - 1], y[pea_shooter.position - 1], &pea_shooter.image[1][0],SRCAND);
	putimage(x[pea_shooter.position - 1], y[pea_shooter.position - 1], &pea_shooter.image[0][0],SRCPAINT);
}

void if_died(int zombie_num) {
	for (int i = 0; i < zombie_num; i++) {
		if (zombies[i].x < 219) {
			gameover = 1;
		}
		if (zombies[i].x == x[pea_shooter.position-1]) {
			gameover = 1;
		}
	}
}