
#include "Scene.h"
#include "DrawableNode.h"
void Scene::DrawAllNodes(Renderer* renderer)
{
	for (std::vector<DrawableNode*>::iterator iter = Childes.begin(); iter != Childes.end(); iter++)
	{
		(*iter)->DrawNode(renderer);
	}
}
