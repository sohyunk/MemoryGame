#include "play.h"

int level = 1;
int check = 0;
int count = 0;
const int MAX_capacity = 20;
int inputCapacity = 4;
int retry = 0;
ArrayStack* Stack = NULL;

int playstatus = 0;		// 0: 기본 1:stack입력 2:stack비교 3:queue입력 4:queue비교 이런식으로
						// while문 두개로 나누지말고 하나로 계속 도는 구조로 만드는게 좋다.
						// 상태를 받아 상태에따라 나눠서 처리
int goto_x = 2;

NodeLQ* Popped;
LinkedQueue* Queue;

// 게임 일정한 틀에서만 출력되도록 만들기
// gotoxy 함수 사용해야 할 것.
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void GuideMessage()
{
	gotoxy(8, 2);
	printf("| ←, → 두개의 화살표를 입력합니다.       |\n");
	gotoxy(8, 3);
	printf("| 종료하고 싶으면 q를 눌러주세요.          |\n");
	gotoxy(8, 4);
	printf("| 3번이상 중복입력시 다시 입력해주세요.    |\n");
	gotoxy(2, 5);
	printf("!!게임시작!!\n");
}

void MenuPrint()
{
	gotoxy(2, 3);
	printf("1. 난이도 ★ (queue)  2. 난이도 ★★ (stack) \n");
	gotoxy(2, 4);
	printf("난이도를 선택해 주세요 : ");
	scanf_s("%d", &check);

	if (check == SelectQueue || check == SelectStack)
	{
		gotoxy(2, 5);
		printf("시작하려면 Spacebar 키를 눌러주세요!!  ");
		int key;
		key = _getch();
		if (key == 32)
		{
			system("cls");
			DrawMap();
			GuideMessage();
			GameMain();
		}
		else
		{
			gotoxy(2, 6);
			printf("잘못 입력했습니다.\n");
		}
	}
	else
	{
		gotoxy(2, 6);
		printf("잘못 입력했습니다.\n");
	}
}

void DrawMap()
{
	for (int i = 0; i < MapHeight; i++)
	{
		for (int j = 0; j < MapWidth; j++)
		{
			if (!(i == 0 || i == MapHeight - 1))
			{
				if ((j == 0 || j == MapWidth - 1))
				{
					printf("□");
				}
				else
				{
					printf("  ");
				}
			}
			else
			{
				printf("□ ");
			}
		}
		printf("\n");
	}
	printf("\n");
}

void CreateCapacity()
{
	if (check == SelectQueue)
	{
		LQ_CreateQueue(&Queue);
	}
	else if (check == SelectStack)
	{
		AS_CreateStack(&Stack, MAX_capacity);
	}
}

void DestroyCapacity()
{
	if (check == SelectQueue)
	{
		LQ_DestroyQueue(Queue);
	}
	else if (check == SelectStack)
	{
		AS_DestroyStack(Stack);
	}
}

void GameMain()
{
	CreateCapacity();
	KeyInput();
	DestroyCapacity();
}

void Update()
{
	level++;
	playstatus = 0;
	goto_x = 2;
	inputCapacity++;
}

void Success()
{
	gotoxy(2, 10);
	printf("성공!!");
	gotoxy(2, 11);
	printf(" - 다음 레벨을 진행합니다. -");
	system("cls");
	Update();
	DrawMap();
	GuideMessage();
}

void Failuer()
{
	printf("×");
	gotoxy(2, 10);
	printf("실패했습니다!!");
	gotoxy(2, 11);
	retry = Retry();

	switch (retry)
	{
	case 1:
		// 제거
		if (check == SelectQueue)
		{
			while (!LQ_IsEmpty(Queue))
			{
				Popped = LQ_Dequeue(Queue);
				LQ_DestroyNode(Popped);
			}		
		}
		else if (check == SelectStack)
		{
			while (!AS_IsEmpty(Stack))
			{
				AS_Pop(Stack);
			}
		}

		// 초기화
		playstatus = 0;
		level = 1;
		count = 0;
		inputCapacity = 4;
		goto_x = 2;
		// 다시 그리기
		system("cls");
		DrawMap();
		GuideMessage();
		break;
	case 2:
		gotoxy(2, 14);
		printf("- 게임을 종료합니다 -");
		exit(0);
		break;
	case 3:
		gotoxy(2, 14);
		printf("- 게임을 종료합니다 -");
		exit(0);
		break;
	}

}

int Retry()
{
	printf("다시 도전하겠습니까? (1) ... 예 / (2) ... 아니오 : ");
	scanf_s("%d", &retry);
	if (retry == 1)
	{
		return 1;
	}
	else if (retry == 2)
	{
		return 2;
	}
	else
	{
		return 3;
	}
}


void KeyInput()
{
	int key;
	int LeftCount = 0;			// 같은 방향 3개 이상 입력 확인용
	int RightCount = 0;

	while (1)
	{
		// system("cls");		화면 지우기
		// 입력

		if (check == SelectQueue)
		{
			if (playstatus == 0)
			{
				if (level == 17)
				{
					gotoxy(2, 6);
					printf(" ★ 게임을 모두 깼습니다 ★");
					gotoxy(2, 7);
					printf(" ! 게임 종료 !\n");
					exit(0);
				}
				else {
					gotoxy(2, 6);
					printf(" -> Level[%d] _ %d개 입력\n", level, inputCapacity);
					playstatus = 1;
					gotoxy(goto_x, 7);
				}
			}
			if (_kbhit())
			{
				key = _getch();
				if (key == 224 || key == 0)
				{
					key = _getch();
					
					switch (key)
					{
					case 75:
						RightCount = 0;
						if (playstatus == 1)
						{
							LeftCount++;
							if (LeftCount > 3)
							{
								printf("?");
							}
							else
							{
								LQ_Enqueue(Queue, LQ_CrateNode(LEFT));
								count++;
								goto_x += 2;
								printf("■");
							}
						}
						else if (playstatus == 2)
						{
							Popped = LQ_Dequeue(Queue);
							if (Popped->Data == LEFT)
							{
								printf("○");
								count--;
								if (count == 0) {
									Success();
								}
								LQ_DestroyNode(Popped);
							}
							else
							{
								Failuer();
							}
						}
						break;

					case 77:
						LeftCount = 0;
						if (playstatus == 1)
						{
							RightCount++;
							if (RightCount > 3)
							{
								printf("?");
							}
							else
							{
								LQ_Enqueue(Queue, LQ_CrateNode(RIGHT));
								count++;
								RightCount;
								goto_x += 2;
								printf("■");
							}
	
						}
						else if (playstatus == 2)
						{
							Popped = LQ_Dequeue(Queue);
							if (Popped->Data == RIGHT)
							{
								printf("○");
								count--;
								if (count == 0) {
									Success();
								}
								LQ_DestroyNode(Popped);
							}
							else
							{
								Failuer();
							}
						}
						break;
					}
				}
				else
				{
					switch (key)
					{
					case 'Q':
					case 'q':
						gotoxy(2, 14);
						printf(" ! 게임 종료 !\n");
						LQ_DestroyQueue(Queue);
						exit(0);
					}
				}
				if (count == inputCapacity)
				{
					playstatus = 2;
					gotoxy(2, 8);
					printf(" - 입력한 순서대로 입력하세요 - ");
					gotoxy(2, 9);
				}
			}
		}
		else if (check == SelectStack)
		{
			if (playstatus == 0)
			{
				if (level == 17)
				{
					gotoxy(2, 6);
					printf(" ★ 게임을 모두 깼습니다 ★");
					gotoxy(2, 7);
					printf(" ! 게임 종료 !\n");
					exit(0);
				}
				else {
					gotoxy(2, 6);
					printf(" -> Level[%d] _ %d개 입력\n", level, inputCapacity);
					playstatus = 1;
					gotoxy(goto_x, 7);
				}
			}
			if (_kbhit())
			{
				key = _getch();
				if (key == 224 || key == 0)
				{
					key = _getch();
					switch (key)
					{
					case 75:
						RightCount = 0;
						if (playstatus == 1)
						{
							LeftCount++;
							if (LeftCount > 3)
							{
								printf("?");
							}
							else
							{
								AS_Push(Stack, LEFT);
								count++;
								goto_x += 2;
								printf("■");
							}						
						}
						else if (playstatus == 2)
						{
							if (AS_Top(Stack) == LEFT)
							{
								AS_Pop(Stack);
								count--;
								printf("○");
								if (count == 0) {
									Success();
								}
							}
							else
							{
								Failuer();
							}
						}
						break;
					case 77:
						LeftCount = 0;
						if (playstatus == 1)
						{
							RightCount++;
							if (RightCount > 3)
							{
								printf("?");
							}
							else
							{
								AS_Push(Stack, RIGHT);
								count++;
								goto_x += 2;
								printf("■");
							}
						}
						else if (playstatus == 2)
						{
							if (AS_Top(Stack) == RIGHT)
							{
								AS_Pop(Stack);
								count--;
								printf("○");
								if (count == 0) {
									Success();
								}
							}
							else
							{
								Failuer();
							}
						}
						break;
					}
				}
				else
				{
					switch (key)
					{
					case 'Q':
					case 'q':
						gotoxy(2, 14);
						printf(" ! 게임 종료 !\n");
						AS_DestroyStack(Stack);
						exit(0);
					}
				}
				if (count == inputCapacity)
				{
					playstatus = 2;
					gotoxy(2, 8);
					printf(" - 입력한 순서와 반대로 입력하세요 - ");
					gotoxy(2, 9);
				}
			}
		}

		// 프로세싱

		// 출력

		Sleep(50);
	}
}