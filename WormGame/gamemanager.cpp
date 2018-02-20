#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "game.h"

GAMEFUNCTION::GameManager * GAMEFUNCTION::GameManager::managerInstance = nullptr;

void gotoxy(int x, int y)
{
	COORD Pos = { 2*x , y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void VisibleCursor(bool visible)
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void SetColor(int color, int bgcolor)
{
	color &= 0xf;
	bgcolor &= 0xf;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
}

void GAMEFUNCTION::GameManager::AddScore(int score)
{
	this->score += score;
}

GAMECONST::GAMEENUM GAMEFUNCTION::GameManager::GetMapType(int x, int y)
{
	if (map[y][x] == GAMECONST::WALL)
	{
		return GAMECONST::WALL;
	}
	if (map[y][x] == GAMECONST::NONE_WALL)
	{
		return GAMECONST::NONE_WALL;
	}
	if (map[y][x] == GAMECONST::HEAD)
	{
		return GAMECONST::HEAD;
	}
	if (map[y][x] == GAMECONST::TAIL)
	{
		return GAMECONST::TAIL;
	}
	if (map[y][x] == GAMECONST::ITEM)
	{
		return GAMECONST::ITEM;
	}
}

void GAMEFUNCTION::GameManager::Render()
{
	using namespace GAMECONST;
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			GAMEENUM type = GetMapType(x, y);
			gotoxy(2 + x, y);
			if(type == WALL)
			{ 
				SetColor(7, 0);
				std::cout << "▣";
			}
			if (type == HEAD)
			{
				SetColor(10, 0);
				std::cout << "◎";
			}
			if (type == TAIL)
			{
				SetColor(9, 0);
				std::cout << "◈";
			}
			if (type == ITEM)
			{
				SetColor(13, 0);
				std::cout << "♥";
			}
		}
		std::cout << std::endl;
	}

	gotoxy(WIDTH + 3, (HEIGHT / 2)-9);
	SetColor(14, 0);
	std::cout << "점수: " << this->score;
}

void GAMEFUNCTION::GameManager::SetGameState(bool type)
{
	state = type;
}

bool GAMEFUNCTION::GameManager::GetGameState() const
{
	return state;
}

bool GAMEFUNCTION::GameManager::CreateWorm()
{
	using namespace GAMECONST;
	if (this->worm != nullptr)
	{
		return false;
	}

	this->worm = new Worm(WIDTH/2-3, (HEIGHT/2)-2);
	this->worm->DrawMap(map);
	return true;
}

bool GAMEFUNCTION::GameManager::WormBodyCheck()
{
	if (this->worm->bodys.size() == 1) return true;
	Worm* head = (Worm*)this->worm->bodys[0];
	for (int i = 1; i < this->worm->bodys.size(); i++)
	{
		int x = head->C_GetLocationX();
		int y = head->C_GetLocationY();
		Body * body = (Body*)this->worm->bodys[i];
		if (body->C_GetLocationX() == x && body->C_GetLocationY() == y) return false;
	}
	return true;
}

bool GAMEFUNCTION::GameManager::WormCheck()
{
	using namespace GAMECONST;
	if (this->worm == nullptr) return false;
	int *x = worm->GetLocationX(), *y = worm->GetLocationY();
	if ((*x == 0 || *x < 0) || *x == WIDTH - 1 || (*y == 0 || *y == HEIGHT - 2 || *y > HEIGHT - 1)) return false;
	return true;
}

void GAMEFUNCTION::GameManager::CreateItem()
{
	if (this->item == nullptr)
	{
		this->item = new Item();
		return;
	}
}

void GAMEFUNCTION::GameManager::ItemRemove()
{
	if (this->item != nullptr)
	{
		this->item->RemoveMap(map);
	}
}

void GAMEFUNCTION::GameManager::Init()
{
	using namespace GAMECONST;
	system("title 지렁이게임 - v1.0 [개발자: 남대영]");
	VisibleCursor(false);
	bool screenState = true;
	while (true)
	{
		if (_kbhit()) break;
		if (screenState)
		{
			gotoxy((WIDTH / 2) + 5, (HEIGHT / 2) - 5);
			SetColor(15, 0);
			std::cout << "→ 지렁이 게임 ←";
			gotoxy((WIDTH / 2) + 6, (HEIGHT / 2) - 2);
			SetColor(15, 0);
			std::cout << "Press any key!";
			screenState = false;
		}
		else
		{
			gotoxy((WIDTH / 2) + 5, (HEIGHT / 2) - 5);
			SetColor(11, 0);
			std::cout << "→ 지렁이 게임 ←";
			gotoxy((WIDTH / 2) + 6, (HEIGHT / 2) - 2);
			SetColor(15, 0);
			std::cout << "Press any key!";
			screenState =true;
		}
		Sleep(500);
	}
	this->Start();
}

void GAMEFUNCTION::GameManager::Start()
{
	using namespace GAMECONST;
	this->SetGameState(true);
	this->CreateItem();
	this->item->ItemDrop();
	this->item->DrawMap(map);
	bool check = true;
	if (this->CreateWorm() && this->GetGameState() == true)
	{
		while (this->GetGameState())
		{
			system("cls");
			if (!WormCheck() || !check)
			{
				this->SetGameState(false);
				break;
			}

			if (!this->item->exists)
			{
				this->item->ItemDrop();
				this->item->DrawMap(map);
			}
			
			for (int i = 0; i < 5; i++)
			{
				if (_kbhit())
				{
					int key = _getch();
					if (key == ESC)
					{
						this->SetGameState(false);
						continue;
					}
					else if(key != SPACE_BAR)
					{
						this->worm->ChangeDirection(key);
					}
				}
			}
			this->worm->RemoveMap(map);
			this->worm->Update(map);
			this->worm->WormMove();
			this->worm->EatItem();
			this->worm->DrawMap(map);
			this->Render();
			check = WormBodyCheck();
			Sleep(100);
		}
	}
	system("cls");
}