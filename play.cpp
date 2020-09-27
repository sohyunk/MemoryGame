#include "play.h"

int level = 1;
int check = 0;
int count = 0;
const int MAX_capacity = 20;
int inputCapacity = 4;
int retry = 0;
ArrayStack* Stack = NULL;

int playstatus = 0;		// 0: �⺻ 1:stack�Է� 2:stack�� 3:queue�Է� 4:queue�� �̷�������
						// while�� �ΰ��� ���������� �ϳ��� ��� ���� ������ ����°� ����.
						// ���¸� �޾� ���¿����� ������ ó��
int goto_x = 2;

NodeLQ* Popped;
LinkedQueue* Queue;

// ���� ������ Ʋ������ ��µǵ��� �����
// gotoxy �Լ� ����ؾ� �� ��.
void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void GuideMessage()
{
	gotoxy(8, 2);
	printf("| ��, �� �ΰ��� ȭ��ǥ�� �Է��մϴ�.       |\n");
	gotoxy(8, 3);
	printf("| �����ϰ� ������ q�� �����ּ���.          |\n");
	gotoxy(8, 4);
	printf("| 3���̻� �ߺ��Է½� �ٽ� �Է����ּ���.    |\n");
	gotoxy(2, 5);
	printf("!!���ӽ���!!\n");
}

void MenuPrint()
{
	gotoxy(2, 3);
	printf("1. ���̵� �� (queue)  2. ���̵� �ڡ� (stack) \n");
	gotoxy(2, 4);
	printf("���̵��� ������ �ּ��� : ");
	scanf_s("%d", &check);

	if (check == SelectQueue || check == SelectStack)
	{
		gotoxy(2, 5);
		printf("�����Ϸ��� Spacebar Ű�� �����ּ���!!  ");
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
			printf("�߸� �Է��߽��ϴ�.\n");
		}
	}
	else
	{
		gotoxy(2, 6);
		printf("�߸� �Է��߽��ϴ�.\n");
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
					printf("��");
				}
				else
				{
					printf("  ");
				}
			}
			else
			{
				printf("�� ");
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
	printf("����!!");
	gotoxy(2, 11);
	printf(" - ���� ������ �����մϴ�. -");
	system("cls");
	Update();
	DrawMap();
	GuideMessage();
}

void Failuer()
{
	printf("��");
	gotoxy(2, 10);
	printf("�����߽��ϴ�!!");
	gotoxy(2, 11);
	retry = Retry();

	switch (retry)
	{
	case 1:
		// ����
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

		// �ʱ�ȭ
		playstatus = 0;
		level = 1;
		count = 0;
		inputCapacity = 4;
		goto_x = 2;
		// �ٽ� �׸���
		system("cls");
		DrawMap();
		GuideMessage();
		break;
	case 2:
		gotoxy(2, 14);
		printf("- ������ �����մϴ� -");
		exit(0);
		break;
	case 3:
		gotoxy(2, 14);
		printf("- ������ �����մϴ� -");
		exit(0);
		break;
	}

}

int Retry()
{
	printf("�ٽ� �����ϰڽ��ϱ�? (1) ... �� / (2) ... �ƴϿ� : ");
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
	int LeftCount = 0;			// ���� ���� 3�� �̻� �Է� Ȯ�ο�
	int RightCount = 0;

	while (1)
	{
		// system("cls");		ȭ�� �����
		// �Է�

		if (check == SelectQueue)
		{
			if (playstatus == 0)
			{
				if (level == 17)
				{
					gotoxy(2, 6);
					printf(" �� ������ ��� �����ϴ� ��");
					gotoxy(2, 7);
					printf(" ! ���� ���� !\n");
					exit(0);
				}
				else {
					gotoxy(2, 6);
					printf(" -> Level[%d] _ %d�� �Է�\n", level, inputCapacity);
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
								printf("��");
							}
						}
						else if (playstatus == 2)
						{
							Popped = LQ_Dequeue(Queue);
							if (Popped->Data == LEFT)
							{
								printf("��");
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
								printf("��");
							}
	
						}
						else if (playstatus == 2)
						{
							Popped = LQ_Dequeue(Queue);
							if (Popped->Data == RIGHT)
							{
								printf("��");
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
						printf(" ! ���� ���� !\n");
						LQ_DestroyQueue(Queue);
						exit(0);
					}
				}
				if (count == inputCapacity)
				{
					playstatus = 2;
					gotoxy(2, 8);
					printf(" - �Է��� ������� �Է��ϼ��� - ");
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
					printf(" �� ������ ��� �����ϴ� ��");
					gotoxy(2, 7);
					printf(" ! ���� ���� !\n");
					exit(0);
				}
				else {
					gotoxy(2, 6);
					printf(" -> Level[%d] _ %d�� �Է�\n", level, inputCapacity);
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
								printf("��");
							}						
						}
						else if (playstatus == 2)
						{
							if (AS_Top(Stack) == LEFT)
							{
								AS_Pop(Stack);
								count--;
								printf("��");
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
								printf("��");
							}
						}
						else if (playstatus == 2)
						{
							if (AS_Top(Stack) == RIGHT)
							{
								AS_Pop(Stack);
								count--;
								printf("��");
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
						printf(" ! ���� ���� !\n");
						AS_DestroyStack(Stack);
						exit(0);
					}
				}
				if (count == inputCapacity)
				{
					playstatus = 2;
					gotoxy(2, 8);
					printf(" - �Է��� ������ �ݴ�� �Է��ϼ��� - ");
					gotoxy(2, 9);
				}
			}
		}

		// ���μ���

		// ���

		Sleep(50);
	}
}