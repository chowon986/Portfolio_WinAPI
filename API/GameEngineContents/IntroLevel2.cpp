// Story0-Mountain ¿Â∏È

#include "IntroLevel2.h"
#include <GameEngineBase/GameEngineWindow.h>

IntroLevel2::IntroLevel2()
{
	// Level_ = nullptr;
}

IntroLevel2::~IntroLevel2()
{
}

void IntroLevel2::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());
}

void IntroLevel2::Render()
{
	DebugRectRender();
}