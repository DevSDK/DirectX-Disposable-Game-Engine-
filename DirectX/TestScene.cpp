#include "TestScene.h"
#include <assert.h>
#include "Sprite.h"

void TestScene::Update(float dt)
{

	test->SetRotateDigree(al+=0.1);
}

TestScene::TestScene()
{
	test= Sprite::Create("Res/test.png",300,168);
	Childes.push_back(test);
	test->SetPosition(100,100);


	auto tt = Sprite::Create("Res/ball.png", 400, 400);
	Childes.push_back(tt);
	tt->SetPosition(-100, -100);

	tt->SetRotateDigree(0);
}


TestScene::~TestScene()
{
}
