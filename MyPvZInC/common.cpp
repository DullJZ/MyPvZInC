#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
#include <Windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>
#include <process.h>
#define WindowWidth 1100
#define WindowHeight 800
static int x[45] = { 262,337,415,496,584,664,742,821,902,261,338,416,497,584,664,742,821,906,261,337,415,501,584,664,741,821,911,261,337,420,501,580,664,742,821,911,257,337,425,501,584,664,742,821,911 };
static int y[45] = { 91 ,87 ,87, 87, 87, 87, 91, 91, 95, 188, 188, 188, 188, 188, 188, 188, 193, 193, 285, 285, 285, 292, 292, 292, 291, 292, 292 ,385, 385, 389, 389, 389, 389, 389, 389, 389, 479 ,479 ,479 ,483 ,483 ,483 ,483 ,483, 483 };
static int y_line[5] = { 83,169,280,365,467 };
static LPCTSTR pea_shooter_images_address_black[13] = { L"./img/peashooterblack/Peashooterblack0.gif",L"./img/peashooterblack/Peashooterblack1.gif",L"./img/peashooterblack/Peashooterblack2.gif",L"./img/peashooterblack/Peashooterblack3.gif",L"./img/peashooterblack/Peashooterblack4.gif",L"./img/peashooterblack/Peashooterblack5.gif",L"./img/peashooterblack/Peashooterblack6.gif",L"./img/peashooterblack/Peashooterblack7.gif",L"./img/peashooterblack/Peashooterblack8.gif",L"./img/peashooterblack/Peashooterblack9.gif",L"./img/peashooterblack/Peashooterblack10.gif",L"./img/peashooterblack/Peashooterblack11.gif",L"./img/peashooterblack/Peashooterblack12.gif"};
static LPCTSTR pea_shooter_images_address_white[13] = { L"./img/peashooterwhite/Peashooterwhite0.gif",L"./img/peashooterwhite/Peashooterwhite1.gif",L"./img/peashooterwhite/Peashooterwhite2.gif",L"./img/peashooterwhite/Peashooterwhite3.gif",L"./img/peashooterwhite/Peashooterwhite4.gif",L"./img/peashooterwhite/Peashooterwhite5.gif",L"./img/peashooterwhite/Peashooterwhite6.gif",L"./img/peashooterwhite/Peashooterwhite7.gif",L"./img/peashooterwhite/Peashooterwhite8.gif",L"./img/peashooterwhite/Peashooterwhite9.gif",L"./img/peashooterwhite/Peashooterwhite10.gif",L"./img/peashooterwhite/Peashooterwhite11.gif",L"./img/peashooterwhite/Peashooterwhite12.gif" };
static LPCTSTR zombie_images_address_black[22] = { L"./img/zombieblack/Zombieblack0.gif",L"./img/zombieblack/Zombieblack1.gif" ,L"./img/zombieblack/Zombieblack2.gif" ,L"./img/zombieblack/Zombieblack3.gif" ,L"./img/zombieblack/Zombieblack4.gif" ,L"./img/zombieblack/Zombieblack5.gif" ,L"./img/zombieblack/Zombieblack6.gif" ,L"./img/zombieblack/Zombieblack7.gif" ,L"./img/zombieblack/Zombieblack8.gif" ,L"./img/zombieblack/Zombieblack9.gif" ,L"./img/zombieblack/Zombieblack10.gif" ,L"./img/zombieblack/Zombieblack11.gif" ,L"./img/zombieblack/Zombieblack12.gif" ,L"./img/zombieblack/Zombieblack13.gif" ,L"./img/zombieblack/Zombieblack14.gif" ,L"./img/zombieblack/Zombieblack15.gif" ,L"./img/zombieblack/Zombieblack16.gif" ,L"./img/zombieblack/Zombieblack17.gif" ,L"./img/zombieblack/Zombieblack18.gif" ,L"./img/zombieblack/Zombieblack19.gif" ,L"./img/zombieblack/Zombieblack20.gif" ,L"./img/zombieblack/Zombieblack21.gif" };
static LPCTSTR zombie_images_address_white[22] = { L"./img/zombiewhite/Zombiewhite0.gif",L"./img/zombiewhite/Zombiewhite1.gif" ,L"./img/zombiewhite/Zombiewhite2.gif" ,L"./img/zombiewhite/Zombiewhite3.gif" ,L"./img/zombiewhite/Zombiewhite4.gif" ,L"./img/zombiewhite/Zombiewhite5.gif" ,L"./img/zombiewhite/Zombiewhite6.gif" ,L"./img/zombiewhite/Zombiewhite7.gif" ,L"./img/zombiewhite/Zombiewhite8.gif" ,L"./img/zombiewhite/Zombiewhite9.gif" ,L"./img/zombiewhite/Zombiewhite10.gif" ,L"./img/zombiewhite/Zombiewhite11.gif" ,L"./img/zombiewhite/Zombiewhite12.gif" ,L"./img/zombiewhite/Zombiewhite13.gif" ,L"./img/zombiewhite/Zombiewhite14.gif" ,L"./img/zombiewhite/Zombiewhite15.gif" ,L"./img/zombiewhite/Zombiewhite16.gif" ,L"./img/zombiewhite/Zombiewhite17.gif" ,L"./img/zombiewhite/Zombiewhite18.gif" ,L"./img/zombiewhite/Zombiewhite19.gif" ,L"./img/zombiewhite/Zombiewhite20.gif" ,L"./img/zombiewhite/Zombiewhite21.gif" };


typedef struct Plant
{
	char name[100];
	IMAGE image[2][13];
	int position;
	int blood;
	int attack_force;
	int attack_speed;
	
} Plant;

typedef struct Zombie
{
	char name[100];
	IMAGE image[2][22];
	int x;
	int line;
	int blood;
	int attack_force;
	int attack_speed;

} Zombie;

typedef struct Bullet
{
	int x, y;
	int fly_speed;
} Bullet;

/*
// 绘图函数，补充透明度
// https://www.cnblogs.com/Bluemultipl/p/15947876.html
void drawAlpha(IMAGE* image, int x, int y, int width, int height, int pic_x, int pic_y, double AA = 1)
{
	// 变量初始化
	DWORD* dst = GetImageBuffer();			// GetImageBuffer() 函数，用于获取绘图设备的显存指针， EasyX 自带
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(image);		// 获取 picture 的显存指针
	int imageWidth = image->getwidth();		// 获取图片宽度
	int imageHeight = image->getheight();	// 获取图片宽度
	int dstX = 0;							// 在 绘图区域 显存里像素的角标
	int srcX = 0;							// 在 image 显存里像素的角标

	// 实现透明贴图 公式： Cp=αp*FP+(1-αp)*BP ， 贝叶斯定理来进行点颜色的概率计算
	for (int iy = 0; iy < height; iy++)
	{
		for (int ix = 0; ix < width; ix++)
		{
			// 防止越界
			if (ix + pic_x >= 0 && ix + pic_x < imageWidth && iy + pic_y >= 0 && iy + pic_y < imageHeight &&
				ix + x >= 0 && ix + x < WindowWidth && iy + y >= 0 && iy + y < WindowHeight)
			{
				// 获取像素角标
				int srcX = (ix + pic_x) + (iy + pic_y) * imageWidth;
				dstX = (ix + x) + (iy + y) * WindowWidth;

				int sa = ((src[srcX] & 0xff000000) >> 24) * AA;			// 0xAArrggbb; AA 是透明度
				int sr = ((src[srcX] & 0xff0000) >> 16);				// 获取 RGB 里的 R
				int sg = ((src[srcX] & 0xff00) >> 8);					// G
				int sb = src[srcX] & 0xff;								// B

				// 设置对应的绘图区域像素信息
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //公式： Cp=αp*FP+(1-αp)*BP  ； αp=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //αp=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //αp=sa/255 , FP=sb , BP=db
			}
		}
	}
}
*/


int play();
void timec_place_zombie(void*);
void timec_move_zombie(void*);
Zombie zombies[100];
Bullet bullets[200];
Plant pea_shooter;
IMAGE common_zombie_img;
IMAGE background;
int zombie_num = 0;