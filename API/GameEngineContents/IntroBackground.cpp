#include "IntroBackground.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

IntroBackground::IntroBackground()
{
	// Level_ = nullptr;
}

IntroBackground::~IntroBackground()
{
}

void IntroBackground::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half()); // ��ġ�� �߾� {1280, 720} {1024, 576}
	//////////////��///// SetScale(GameEngineWindow::GetScale()); // ������ ũ�� -> �ش� �κ� �˾ƺ���
	GameEngineRenderer* a = CreateRenderer("BackgroundB.bmp");
}

void IntroBackground::Update()
{

}

void IntroBackground::Render()
{
	DebugRectRender();
}