#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>		// ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#define WindowWidth 1100
#define WindowHeight 800
static int x[45] = { 262,337,415,496,584,664,742,821,902,261,338,416,497,584,664,742,821,906,261,337,415,501,584,664,741,821,911,261,337,420,501,580,664,742,821,911,257,337,425,501,584,664,742,821,911 };
static int y[45] = { 91 ,87 ,87, 87, 87, 87, 91, 91, 95, 188, 188, 188, 188, 188, 188, 188, 193, 193, 285, 285, 285, 292, 292, 292, 291, 292, 292 ,385, 385, 389, 389, 389, 389, 389, 389, 389, 479 ,479 ,479 ,483 ,483 ,483 ,483 ,483, 483 };


typedef struct Plant
{
	char name[100];
	char image_path[200];
	int position;
	int blood;
	int attack_force;
	int attack_speed;
	
} Plant;

typedef struct Zombie
{
	char name[100];
	int x, y;
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
// ��ͼ����������͸����
// https://www.cnblogs.com/Bluemultipl/p/15947876.html
void drawAlpha(IMAGE* image, int x, int y, int width, int height, int pic_x, int pic_y, double AA = 1)
{
	// ������ʼ��
	DWORD* dst = GetImageBuffer();			// GetImageBuffer() ���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬 EasyX �Դ�
	DWORD* draw = GetImageBuffer();
	DWORD* src = GetImageBuffer(image);		// ��ȡ picture ���Դ�ָ��
	int imageWidth = image->getwidth();		// ��ȡͼƬ���
	int imageHeight = image->getheight();	// ��ȡͼƬ���
	int dstX = 0;							// �� ��ͼ���� �Դ������صĽǱ�
	int srcX = 0;							// �� image �Դ������صĽǱ�

	// ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
	for (int iy = 0; iy < height; iy++)
	{
		for (int ix = 0; ix < width; ix++)
		{
			// ��ֹԽ��
			if (ix + pic_x >= 0 && ix + pic_x < imageWidth && iy + pic_y >= 0 && iy + pic_y < imageHeight &&
				ix + x >= 0 && ix + x < WindowWidth && iy + y >= 0 && iy + y < WindowHeight)
			{
				// ��ȡ���ؽǱ�
				int srcX = (ix + pic_x) + (iy + pic_y) * imageWidth;
				dstX = (ix + x) + (iy + y) * WindowWidth;

				int sa = ((src[srcX] & 0xff000000) >> 24) * AA;			// 0xAArrggbb; AA ��͸����
				int sr = ((src[srcX] & 0xff0000) >> 16);				// ��ȡ RGB ��� R
				int sg = ((src[srcX] & 0xff00) >> 8);					// G
				int sb = src[srcX] & 0xff;								// B

				// ���ö�Ӧ�Ļ�ͼ����������Ϣ
				int dr = ((dst[dstX] & 0xff0000) >> 16);
				int dg = ((dst[dstX] & 0xff00) >> 8);
				int db = dst[dstX] & 0xff;
				draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
					| ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
					| (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
			}
		}
	}
}
*/

