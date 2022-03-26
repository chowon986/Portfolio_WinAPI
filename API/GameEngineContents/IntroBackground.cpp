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
	SetPosition(GameEngineWindow::GetScale().Half()); // 위치는 중앙 {1280, 720} {1024, 576}
	//////////////초///// SetScale(GameEngineWindow::GetScale()); // 엑터의 크기 -> 해당 부분 알아보기
	GameEngineRenderer* a = CreateRenderer("BackgroundB.bmp");
}

void IntroBackground::Update()
{

}

void IntroBackground::Render()
{
	DebugRectRender();
}