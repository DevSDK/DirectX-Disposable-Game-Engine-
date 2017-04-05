#pragma once
#include "Scene.h"
class SceneManager
{
public:
	static SceneManager* GetInstance();
	void SetScene(Scene* scene);
	Scene* GetCurrentScene();

private:
	static SceneManager* Instance; 
	SceneManager();
	~SceneManager();
	Scene* CurrentScene = NULL;
	
	

};

