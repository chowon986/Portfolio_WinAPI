#include "IntroBackground.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

IntroBackground::IntroBackground()
{
}

IntroBackground::~IntroBackground()
{
}

void IntroBackground::Start()
{
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