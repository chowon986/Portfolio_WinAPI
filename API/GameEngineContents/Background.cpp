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
	SetPosition(GameEngineWindow::GetScale().Half() + float4(0, GetScale().y));
}

void Background::Render()
{
	DebugRectRender();
}