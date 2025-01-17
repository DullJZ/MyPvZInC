#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
#include <math.h>
#include <Windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>
#include <process.h>
#pragma comment(lib,"winmm.lib")
#include <mmsystem.h>
#define WindowWidth 1100
#define WindowHeight 800
static int x[45] = { 262,337,415,496,584,664,742,821,902,261,338,416,497,584,664,742,821,906,261,337,415,501,584,664,741,821,911,261,337,420,501,580,664,742,821,911,257,337,425,501,584,664,742,821,911 };
static int y[45] = { 91 ,87 ,87, 87, 87, 87, 91, 91, 95, 188, 188, 188, 188, 188, 188, 188, 193, 193, 285, 285, 285, 292, 292, 292, 291, 292, 292 ,385, 385, 389, 389, 389, 389, 389, 389, 389, 479 ,479 ,479 ,483 ,483 ,483 ,483 ,483, 483 };
static int y_line[5] = { 83,169,280,365,467 };
static LPCTSTR pea_shooter_images_address_black[13] = { L"./img/black/Peashooterblack0.gif",L"./img/black/Peashooterblack1.gif",L"./img/black/Peashooterblack2.gif",L"./img/black/Peashooterblack3.gif",L"./img/black/Peashooterblack4.gif",L"./img/black/Peashooterblack5.gif",L"./img/black/Peashooterblack6.gif",L"./img/black/Peashooterblack7.gif",L"./img/black/Peashooterblack8.gif",L"./img/black/Peashooterblack9.gif",L"./img/black/Peashooterblack10.gif",L"./img/black/Peashooterblack11.gif",L"./img/black/Peashooterblack12.gif"};
static LPCTSTR pea_shooter_images_address_white[13] = { L"./img/white/Peashooterwhite0.gif",L"./img/white/Peashooterwhite1.gif",L"./img/white/Peashooterwhite2.gif",L"./img/white/Peashooterwhite3.gif",L"./img/white/Peashooterwhite4.gif",L"./img/white/Peashooterwhite5.gif",L"./img/white/Peashooterwhite6.gif",L"./img/white/Peashooterwhite7.gif",L"./img/white/Peashooterwhite8.gif",L"./img/white/Peashooterwhite9.gif",L"./img/white/Peashooterwhite10.gif",L"./img/white/Peashooterwhite11.gif",L"./img/white/Peashooterwhite12.gif" };

typedef struct Plant
{
	char name[100];
	int now_img_index = 0;
	IMAGE image[2][13];
	int position;
	int line; //0~4
	int blood;
	int attack_force;
	int attack_speed;
	
} Plant;

typedef struct Zombie
{
	char name[100];
	int x;
	int line;
	int blood;
	int alive = 1; //为1代表存活
	int attack_force;
	int attack_speed;

} Zombie;


typedef struct Bullet
{
	int type = 1; //为0代表普通子弹，为1代表超级子弹
	int x;
	int line;
	int flag = 0; //为0代表未击中，可视
	int hurt = 20;
} Bullet;

int play();
void timec_place_zombie(void*);
void timec_move_zombie(void*);
void timec_cartoon(void*);
void timec_place_bullet(void*);
void timec_move_bullet(void*);
void timec_refresh(void*);
void timec_check(void*);
void timec_rubbish_collect(void*);
void timec_bgm(void*);
void timec_superbullet(void*);
void if_died(int);
void LoadPeashooter();
void PaintPeashooter();
int get_perfect_shoot_arg(int);
void heart(int x0, int y0, int size, COLORREF C);
Zombie zombies[100];
Bullet bullets[1000];
Plant pea_shooter;
IMAGE zombie_img_black;
IMAGE zombie_img_white;
IMAGE bullet_img_black;
IMAGE bullet_img_white;
IMAGE fire_img_black;
IMAGE fire_img_white;
IMAGE grayfire_img_black;
IMAGE grayfire_img_white;
IMAGE gameover_img;
IMAGE superbullet_img_black;
IMAGE superbullet_img_white;
IMAGE background;
int zombie_num = 0;
int dead_zombie_num = 0;
int bullet_num = 0;
int gameover = 0;
int fire_available = 1;
__int64 start_time = 0;