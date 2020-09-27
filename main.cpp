#include "play.h"

int main()
{
	// 화면 0,0 부터 시작
	DrawMap();
	gotoxy(1, 2);
	printf("\t\t  *** 기억력 게임 *** \n");

	MenuPrint();

}