#include "common.cpp"
void clear(IMAGE background) {
	{
		// «Â∆¡
		cleardevice();
		// ªÊ÷∆±≥æ∞
		putimage(0, 0, &background);
	}
}