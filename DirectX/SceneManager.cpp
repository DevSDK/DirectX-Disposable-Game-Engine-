#include "SceneManager.h"

SceneManager* SceneManager::Instance = NULL;

SceneManager* SceneManager::GetInstance()
{
	if (Instance == NULL)
		Instance = new SceneManager();
	return Instance;
}

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}

void SceneManager::SetScene(Scene * scene)
{
	if (CurrentScene != NULL)
		delete CurrentScene;
	CurrentScene = scene;
}

Scene* SceneManager::GetCurrentScene()
{
	return CurrentScene;
}
