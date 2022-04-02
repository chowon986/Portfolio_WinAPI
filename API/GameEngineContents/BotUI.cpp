#include "BotUI.h"

BotUI::BotUI()
{
}

BotUI::~BotUI()
{
}


void BotUI::Start()
{
}

void BotUI::Render()
{
	GameEngineRenderer* PlayerUI = CreateRenderer("NormalStatus.bmp",RenderPivot::CENTER,float4(49.0f,557.0f));

}