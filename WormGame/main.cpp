#include <iostream>
#include "game.h"

int main(void)
{
	GAMEFUNCTION::GameManager * manager = GAMEFUNCTION::GameManager::GetGameManager();
	manager->Init();

	manager->DeleteManager();
	
	system("pause");
	return 0;
}
