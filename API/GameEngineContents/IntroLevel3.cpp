// Story1-Garden 

#include "IntroLevel3.h"
#include <GameEngineBase/GameEngineWindow.h>

IntroLevel3::IntroLevel3()
{
	// Level_ = nullptr;
}

IntroLevel3::~IntroLevel3()
{
}

void IntroLevel3::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());
}

void IntroLevel3::Render()
{
	DebugRectRender();
}