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
	// 크기 조절 모르겠음
	SetPosition(GameEngineWindow::GetScale().Half() + float4(0, GetScale().y));
}

void Background::Render()
{
	DebugRectRender();
}