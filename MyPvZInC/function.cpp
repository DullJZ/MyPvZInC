#include "common.cpp"
void clear(IMAGE background) {
	{
		// ����
		cleardevice();
		// ���Ʊ���
		putimage(0, 0, &background);
	}
}