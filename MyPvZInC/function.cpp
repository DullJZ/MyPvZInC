#include "common.cpp"
void fresh(IMAGE background,Plant pea_shooter,Zombie zombies[]) {
	{
		// 清屏
		cleardevice();
		// 绘制背景
		putimage(0, 0, &background);
		// 绘制植物
		putimage(x[pea_shooter.position], y[pea_shooter.position], &pea_shooter.image);
	}
}

int get_remain_time(int start_time){
	return time(NULL) - start_time;
}