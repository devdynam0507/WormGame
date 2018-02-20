#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "game.h"

using namespace GAMEFUNCTION;

void Item::DrawMap(int(*map)[GAMECONST::WIDTH])
{
	map[this->locY][this->locX] = GAMECONST::ITEM;
}

void Item::RemoveMap(int(*map)[GAMECONST::WIDTH])
{
	map[locY][locX] = GAMECONST::NONE_WALL;
}

int* Item::GetLocationX()
{
	return &locX;
}

int* Item::GetLocationY()
{
	return &locY;
}

int Item::C_GetLocationX() const
{
	return locX;
}

int Item::C_GetLocationY() const
{
	return locY;
}

void Item::SetPosition(GAMECONST::ObjectMovingType constMovingType, int setX, int setY)
{
	switch (constMovingType)
	{
	case GAMECONST::ObjectMovingType::DROP:
		int *x = GetLocationX();
		int *y = GetLocationY();
		*x = setX;
		*y = setY;
		exists = true;
		break;
	}
}

void Item::ItemDrop()
{
	srand(time(NULL));

	int x = 2 + (rand() % (GAMECONST::WIDTH - 3));
	int y = 3 + (rand() % (GAMECONST::HEIGHT - 5));

	this->SetPosition(GAMECONST::DROP, x, y);
}

std::string Item::type()
{
	return "Item";
}
