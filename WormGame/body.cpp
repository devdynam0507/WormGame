#include <iostream>
#include "game.h"

using namespace GAMEFUNCTION;

void Body::DrawMap(int(*map)[GAMECONST::WIDTH])
{
	map[this->locY][this->locX] = GAMECONST::TAIL;
}

void Body::RemoveMap(int(*map)[GAMECONST::WIDTH])
{
	map[this->locY][this->locX] = GAMECONST::NONE_WALL;
}

int * Body::GetLocationX()
{
	return &locX;
}

int * Body::GetLocationY()
{
	return &locY;
}

int Body::C_GetLocationX() const
{
	return locX;
}

int Body::C_GetLocationY() const
{
	return locY;
}

void Body::SetPosition(GAMECONST::ObjectMovingType constMovingType, int setX, int setY)
{
	switch (constMovingType)
	{
	case GAMECONST::ObjectMovingType::MOVE:
		this->locX = setX;
		this->locY = setY;
		break;
	}
}

void Body::ReservationLocation(int x, int y)
{
	this->nextLocX = x;
	this->nextLocY = y;
}

void Body::Update(int(*map)[GAMECONST::WIDTH])
{
	this->DrawMap(map);
}

void Body::Update()
{
	this->locX = this->nextLocX;
	this->locY = this->nextLocY;
}

std::string Body::type()
{
	return "Worm Body";
}