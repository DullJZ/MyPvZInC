#include "common.cpp"
void PaintPeashooter();
void fresh(IMAGE background,Plant pea_shooter,Zombie zombies[]) {
	{
		// ����
		cleardevice();
		// ���Ʊ���
		putimage(0, 0, &background);
		// ����ֲ��
		PaintPeashooter();
		// ���ƽ�ʬ
		for (int i = 1; i <= zombie_num; i++) {
			putimage(zombies[i-1].x, y_line[zombies[i-1].line], &common_zombie_img);
		}
	}
}

int get_remain_time(int start_time){
	return time(NULL) - start_time;
}

int place_zombie(Zombie zombies[],IMAGE zombie_img, int zombie_num) {
	/* ��ʼ������������� */
	time_t t;
	srand((unsigned)time(&t));
	zombies[zombie_num-1].line = rand() % 5; // ����0~5֮��������
	// ���ý�ʬ
	strcpy(zombies[zombie_num-1].name, "��ͨ��ʬ");
	zombies[zombie_num - 1].blood = 100;
	zombies[zombie_num - 1].x = 975;
	loadimage(&zombie_img, L"./img/Zombie.gif",0,0);
	putimage(975, y_line[zombies[zombie_num - 1].line]-100, &zombie_img);
	return 0;
}

int move_zombie(Zombie *zombie) {
	zombie->x -= 20;
	fresh(background, pea_shooter, zombies);
	return 0;
}

void LoadPeashooter(IMAGE Peashooter_img[2][13])
{
	for (int i = 0; i < 13; i++)
	{
		loadimage(&Peashooter_img[0][i], pea_shooter_images_address_black[i]);//����ڵײ�ͼ
		loadimage(&Peashooter_img[1][i], pea_shooter_images_address_white[i]);//����׵׺�ͼ
	}
}

void LoadZombies(IMAGE Zombie_img[2][13]) {
	for (int i = 0; i < 22; i++)
	{
		loadimage(&Zombie_img[0][i], zombie_images_address_black[i]);//����ڵײ�ͼ
		loadimage(&Zombie_img[1][i], zombie_images_address_white[i]);//����׵׺�ͼ
	}
}

void PaintPeashooter() {
	for (int i = 0; i < 13; i++)
	{
		putimage(x[pea_shooter.position - 1], y[pea_shooter.position - 1], &pea_shooter.image[1][i],SRCAND);
		putimage(x[pea_shooter.position - 1], y[pea_shooter.position - 1], &pea_shooter.image[0][i],SRCPAINT);
	}
}

void PaintZombie(Zombie zombie) {
	for (int i = 0; i < 22; i++)
	{
		putimage(zombie.x, y_line[zombie.line], &pea_shooter.image[1][i], SRCAND);
		putimage(x[pea_shooter.position - 1], y[pea_shooter.position - 1], &pea_shooter.image[0][i], SRCPAINT);
	}
}