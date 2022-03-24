// 나무 장면

#include "IntroLevel1.h"
#include <GameEngineBase/GameEngineWindow.h>

IntroLevel1::IntroLevel1()
{
	// Level_ = nullptr;
}

IntroLevel1::~IntroLevel1()
{
}

void IntroLevel1::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());
}

void IntroLevel1::Render()
{
	DebugRectRender();
}