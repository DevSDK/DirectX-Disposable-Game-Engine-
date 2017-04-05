#pragma once
#include "Scene.h"
#include "Sprite.h"

class TestScene :public Scene
{
	float al = 0;
public:
	Sprite* test;
	virtual void Update(float dt);
	TestScene();
	~TestScene();
};

