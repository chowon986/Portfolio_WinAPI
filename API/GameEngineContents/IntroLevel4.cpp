// Story2 - To the castle

#include "IntroLevel4.h"
#include <GameEngineBase/GameEngineWindow.h>

IntroLevel4::IntroLevel4()
{
	// Level_ = nullptr;
}

IntroLevel4::~IntroLevel4()
{
}

void IntroLevel4::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());
}

void IntroLevel4::Render()
{
	DebugRectRender();
}