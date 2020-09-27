#ifndef PLAY_H
#define PLAY_H

#include "ArrayStack.h"
#include "LinkedQueue.h"
#include <conio.h>
#include <Windows.h>

#define LEFT 1
#define RIGHT 2
#define SelectQueue 1
#define SelectStack 2 
#define MapWidth 30
#define MapHeight 28

void gotoxy(int x, int y);
void CreateCapacity();
void DestroyCapacity();
void MenuPrint();
void GameMain();
void DrawMap();

void KeyInput();
int Retry();
void Success();
void Failuer();

#endif