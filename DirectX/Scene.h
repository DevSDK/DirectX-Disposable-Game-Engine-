#pragma once
#include <vector>
class Renderer;
class DrawableNode;
class Scene 
{
public:
	
	void DrawAllNodes(Renderer* );
	virtual void Update(float dt) = 0;
protected:
	std::vector<DrawableNode*> Childes;
};