#include "common.cpp"
void fresh(IMAGE background,Plant pea_shooter,Zombie zombies[]) {
	{
		// ����
		cleardevice();
		// ���Ʊ���
		putimage(0, 0, &background);
		// ����ֲ��
		putimage(x[pea_shooter.position], y[pea_shooter.position], &pea_shooter.image);
	}
}

int get_remain_time(int start_time){
	return time(NULL) - start_time;
}