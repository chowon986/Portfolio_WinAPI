// Nintendo ¿Â∏È

#include "IntroLevel0.h"
#include <GameEngineBase/GameEngineWindow.h>

IntroLevel0::IntroLevel0()
{
	// Level_ = nullptr;
}

IntroLevel0::~IntroLevel0()
{
}

void IntroLevel0::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());
}

void IntroLevel0::Render()
{
	DebugRectRender();
}