#include "Background.h"
#include <GameEngineBase/GameEngineWindow.h>

Background::Background()
{
	// Level_ = nullptr;
}

Background::~Background()
{
}

void Background::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());
}

void Background::Render()
{
	DebugRectRender();
}