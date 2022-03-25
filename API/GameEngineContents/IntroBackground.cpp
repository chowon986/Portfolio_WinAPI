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
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());

	GameEngineRenderer* a = CreateRenderer("BackgroundB.bmp");
}

void IntroBackground::Update()
{

}

void IntroBackground::Render()
{
	DebugRectRender();
}