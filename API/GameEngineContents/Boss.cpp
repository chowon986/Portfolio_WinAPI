#include "Boss.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include "Background.h"
#include "ContentsEnum.h"

Boss::Boss()
{
}

Boss::~Boss()
{
}


void Boss::Loading()
{
	CreateActor<Background>((int)ORDER::BACKGROUND);
}

void Boss::Update()
{
}

void Boss::LevelChangeStart()
{
	{
		Background* Boss = CreateActor<Background>((int)ORDER::BACKGROUND);
		Boss->CreateRenderer(".bmp", RenderPivot::CENTER, float4(1920.0f, 0.0f));
	}
}
