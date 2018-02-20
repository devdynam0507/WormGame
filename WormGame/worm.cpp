#include <iostream>
#include "game.h"


using namespace GAMEFUNCTION;

void Worm::DrawMap(int (*map)[GAMECONST::WIDTH])
{
	map[this->locY][this->locX] = GAMECONST::HEAD;
}

void Worm::RemoveMap(int(*map)[GAMECONST::WIDTH])
{
	map[this->locY][this->locX] = GAMECONST::NONE_WALL;
}

int* Worm::GetLocationX() 
{
	return &locX;
}

int* Worm::GetLocationY()
{
	return &locY;
}

int Worm::C_GetLocationX() const
{
	return locX;
}

int Worm::C_GetLocationY() const
{
	return locY;
}

void Worm::SetPosition(GAMECONST::ObjectMovingType typeConst, int addX, int addY)
{
	switch (typeConst)
	{
	case GAMECONST::ObjectMovingType::MOVE:
		int *x = GetLocationX();
		int *y = GetLocationY();
		*x = addX;
		*y = addY;
		break;
	}
}

void Worm::MoveLeft()
{
	int *x = GetLocationX();
	if (*x - 1 < 0)
	{
		return;
	}

	*x -= 1;
}

void Worm::MoveRight()
{
	int *x = GetLocationX();
	if (*x + 1 == GAMECONST::WIDTH)
	{
		return;
	}

	*x += 1;
}

void Worm::MoveDown()
{
	int *y = GetLocationY();
	if (*y + 1 == GAMECONST::HEIGHT - 1) return;

	*y += 1;
}

void Worm::MoveUp()
{
	int *y = GetLocationY();
	if (*y - 1 < 0) return;

	*y -= 1;
}

void Worm::WormMove()
{
	switch (this->headDirection)
	{
	case GAMECONST::WormHeadDirection::H_UP:
		MoveUp();
		break;
	case GAMECONST::WormHeadDirection::H_DOWN:
		MoveDown();
		break;
	case GAMECONST::WormHeadDirection::H_LEFT:
		MoveLeft();
		break;
	case GAMECONST::WormHeadDirection::H_RIGHT:
		MoveRight();
		break;
	default:
		break;
	}
}

void Worm::ChangeDirection(int constKeyType)
{
	if (!IsWay(headDirection, constKeyType)) return;
	switch (constKeyType)
	{
	case GAMECONST::KEY::LEFT:
		this->headDirection = GAMECONST::WormHeadDirection::H_LEFT;
		break;
	case GAMECONST::KEY::RIGHT:
		this->headDirection = GAMECONST::WormHeadDirection::H_RIGHT;
		break;
	case GAMECONST::KEY::UP:
		this->headDirection = GAMECONST::WormHeadDirection::H_UP;
		break;
	case GAMECONST::KEY::DOWN:
		this->headDirection = GAMECONST::WormHeadDirection::H_DOWN;
		break;
	default:
		break;
	}
}

bool Worm::IsWay(GAMECONST::WormHeadDirection headDirection, int changeDirection)
{
	if (headDirection == GAMECONST::WormHeadDirection::H_UP && changeDirection == GAMECONST::DOWN) return false;
	if (headDirection == GAMECONST::WormHeadDirection::H_DOWN && changeDirection == GAMECONST::UP) return false;
	if (headDirection == GAMECONST::WormHeadDirection::H_LEFT && changeDirection == GAMECONST::RIGHT) return false;
	if (headDirection == GAMECONST::WormHeadDirection::H_RIGHT && changeDirection == GAMECONST::LEFT) return false;
	return true;
}

void Worm::EatItem()
{
	if (GameManager::GetGameManager()->GetMapType(locX, locY) == GAMECONST::ITEM)
	{
		eat = true;
		GameManager::GetGameManager()->ItemRemove();
		GameManager::GetGameManager()->item->exists = false;

		GameObject* object = bodys.back();
		int x = object->C_GetLocationX();
		int y = object->C_GetLocationY();

		Body * body = new Body(x, y);
		body->ReservationLocation(x, y);
		
		next.push(body);
		newTail = true;
		GameManager::GetGameManager()->AddScore(100);
	}
}

std::string Worm::type()
{
	return "Worm Head";
}

/* 헤드의 위치 변경이 일어난후 붙어있는 Body는 정상작동함. 근데 그 이후의 바디에선 값변경이 일어나질 않음.*/
void Worm::Update(int(*map)[GAMECONST::WIDTH])
{
	if (newTail && next.size() > 0)
	{
		GameObject * object = next.front();
		this->bodys.push_back(object);
		newTail = false;
		next.pop();
	}

	int x = bodys[0]->C_GetLocationX(), y = bodys[0]->C_GetLocationY();
	if (bodys.size() > 1)
	{
		Body* fbody = (Body*) bodys[1];
		fbody->ReservationLocation(x, y);
		for (int i = 1; i < bodys.size(); i++)
		{
			if (i == 0) continue;
			if (i + 1 < bodys.size())
			{
				Body* fb = (Body*)bodys[i];
				Body* body = (Body*)bodys[i + 1];
				body->ReservationLocation(fb->C_GetLocationX(), fb->C_GetLocationY());
			}
		}

		for (int i = 1; i < bodys.size(); i++)
		{
			Body * b = (Body*)bodys[i];
			b->RemoveMap(map);
			b->Update();
			b->Update(map);
		}
	}
}

void Worm::PrintWorms()
{
	for (int i = 0; i < bodys.size(); i++)
	{
		std::cout << bodys[i]->type().c_str() << " " << bodys[i]->C_GetLocationX() << " " << bodys[i]->C_GetLocationY() << " " << bodys[i] << " - ";
	}
}