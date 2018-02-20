#pragma once
#ifndef __GAME_H__
#define __GAME_H__
#include <vector>
#include <queue>

namespace GAMECONST
{
	enum GAMEENUM
	{
		WIDTH = 40,
		HEIGHT = 28,
		WALL = 1,
		NONE_WALL = 0,
		EXCEPTION = -1,

		HEAD = 1000,
		TAIL = 999,
		ITEM = 998
	};

	enum KEY
	{
		UP = 72,
		DOWN = 80,
		LEFT = 75,
		RIGHT = 77,
		ESC = 27,
		SPACE_BAR = 32
	};

	enum ObjectMovingType
	{
		MOVE,
		DROP
	};

	enum WormHeadDirection
	{
		H_LEFT, H_RIGHT, H_UP, H_DOWN
	};
}

namespace GAMEFUNCTION
{

	class GameObject /* 오브젝트 추상 클래스 */
	{
	protected:
		int locX, locY;

	public:
		virtual int* GetLocationX() = 0;
		virtual int* GetLocationY() = 0;
		virtual int C_GetLocationX() const = 0;
		virtual int C_GetLocationY() const = 0;
		virtual void DrawMap(int(*map)[GAMECONST::WIDTH]) = 0;
		virtual void SetPosition(GAMECONST::ObjectMovingType, int x, int y) = 0;
		virtual void RemoveMap(int(*map)[GAMECONST::WIDTH]) = 0;
		virtual std::string type() = 0;
	};

	class Move /* 움직이는 오브젝트 추상 클래스 */
	{
	public:
		virtual void MoveLeft() = 0;
		virtual void MoveRight() = 0;
		virtual void MoveUp() = 0;
		virtual void MoveDown() = 0;
	};

	class Body : public GameObject
	{
	public:
		int nextLocX, nextLocY;

	public:

		Body(int locX, int locY)
		{
			this->locX = locX;
			this->locY = locY;
		}

	public:
		virtual void DrawMap(int(*map)[GAMECONST::WIDTH]);
		virtual void RemoveMap(int(*map)[GAMECONST::WIDTH]);
		virtual int* GetLocationX();
		virtual int* GetLocationY();
		virtual int C_GetLocationX() const;
		virtual int C_GetLocationY() const;
		virtual void SetPosition(GAMECONST::ObjectMovingType, int addX, int addY);
		virtual std::string type();
		void Update(int(*map)[GAMECONST::WIDTH]);
		void Update();
		void ReservationLocation(int x, int y);
	};


	class Worm : public GameObject, public Move
	{
	private:
		std::queue<GameObject*> next;

	public:
		GAMECONST::WormHeadDirection headDirection;
		bool eat;
		bool newTail;
		std::vector<GameObject*> bodys;

	public:
		Worm(int locX, int locY)
		{
			this->headDirection = GAMECONST::WormHeadDirection::H_RIGHT;
			this->locX = locX;
			this->locY = locY;
			bodys.push_back(this);
			newTail = false;
		}

	public:
		virtual void DrawMap(int(*map)[GAMECONST::WIDTH]);
		virtual void RemoveMap(int(*map)[GAMECONST::WIDTH]);
		virtual int* GetLocationX();
		virtual int* GetLocationY();
		virtual void SetPosition(GAMECONST::ObjectMovingType, int addX, int addY);
		virtual void MoveLeft();
		virtual void MoveRight();
		virtual void MoveUp();
		virtual void MoveDown();
		virtual int C_GetLocationX() const;
		virtual int C_GetLocationY() const;
		virtual std::string type();
		void WormMove();
		void ChangeDirection(int key);
		bool IsWay(GAMECONST::WormHeadDirection, int constKey);
		void EatItem();
		void Update(int(*map)[GAMECONST::WIDTH]);
		void PrintWorms();
	};

	class Item : public GameObject
	{
	public:
		bool exists = false;

	public:
		Item()
		{
			this->locX = 2;
			this->locY = 2;
		}

	public:
		virtual void DrawMap(int(*map)[GAMECONST::WIDTH]);
		virtual void RemoveMap(int(*map)[GAMECONST::WIDTH]);
		virtual int* GetLocationX();
		virtual int* GetLocationY();
		virtual int C_GetLocationX() const;
		virtual int C_GetLocationY() const;
		virtual void SetPosition(GAMECONST::ObjectMovingType, int setX, int setY);
		virtual std::string type();
		void ItemDrop();

	};

	class GameManager
	{
	public:
		Item * item = nullptr;

	private:
		int map[GAMECONST::HEIGHT][GAMECONST::WIDTH] =
		{
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		};

		bool state;
		static GameManager * managerInstance;
		Worm * worm = nullptr;

		int score = 0;

	private:
		GameManager()
		{
		}

		~GameManager()
		{
			std::cout << "GameMananger Closed" << std::endl;
		}
	public:
		static GameManager* GetGameManager()
		{
			if (managerInstance == nullptr)
			{
				managerInstance = new GameManager();
			}
			return managerInstance;
		}

	public:
		void Render(); /* 맵을 렌더링 합니다. */
		GAMECONST::GAMEENUM GetMapType(int x, int y); /* 해당 좌표의 GAMEENUM 을 받아옵니다.*/
		void SetGameState(bool state); /* 게임상태를 바꿉니다. */
		bool GetGameState() const; /* 게임상태를 가져옵니다.*/
		bool CreateWorm(); /* 지렁이를 생성합니다. 1회 생성밖에 안됩니다. */
		void Start(); /* 게임을 시작합니다. */
		bool WormCheck(); /* 지렁이의 머리가 부딪혔는지 체크합니다. */
		void CreateItem(); /* 아이템을 생성합니다. */
		void ItemRemove(); /* 아이템을 삭제합니다. */
		bool WormBodyCheck(); /* 지렁이의 머리가 몸에 부딪혔는지 체크합니다. !(WormCheck() 코드가 길어지므로 함수로 뺌)*/
		void AddScore(int score);
		void Init(); /* 게임 시작전 준비창 */
		void DeleteManager(); /* 싱글톤 해제 */
	};
}

#endif
