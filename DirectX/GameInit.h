#pragma once
#include "Scene.h"
#include "TestScene.h"
class GameInitalize
{
	static GameInitalize* Instance;
public:
	static GameInitalize* GetInstance();

	void Main();

	~GameInitalize();
};