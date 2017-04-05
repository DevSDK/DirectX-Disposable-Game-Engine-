#include "GameInit.h"
#include "SceneManager.h"
GameInitalize* GameInitalize::Instance = NULL;

GameInitalize* GameInitalize::GetInstance()
{
	if (Instance == NULL)
		Instance = new GameInitalize();
	return Instance;
}

void GameInitalize::Main()
{
	TestScene* test = new TestScene();
	SceneManager::GetInstance()->SetScene(test);
}

GameInitalize::~GameInitalize()
{ 
	delete Instance;
}
