#include "Doc.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>


Doc::Doc()
	: Monster()
	, ColMapImage_(nullptr)
	, Level_(nullptr)
{
}

Doc::~Doc()
{
}

void Doc::Start()
{
	GameEngineLevel* Level = GetLevel();
	ColMapImage_ = Level->GetColMapImage();

	GameEngineRenderer* DocRenderer = CreateRenderer("monster0.bmp");
	GameEngineImage* DocImage = DocRenderer->GetImage();
	DocImage->CutCount(10, 26);
	DocRenderer->CreateAnimation("monster0.bmp", "DocIdle", 160, 164, 0.3f, true);
	DocRenderer->ChangeAnimation("DocIdle");

}


void Doc::Render()
{
}

void Doc::Update()
{
	//PrevPos_ = GetPosition();

	//float4 NewPos;
	//NewPos.x = GetPosition().x + GameEngineTime::GetDeltaTime() * GetSpeed();
	//NewPos.y = GetPosition().y;
	//SetPosition(NewPos);

	//if (true == CheckMapCollision())
	//{
	//	SetPosition(PrevPos_);
	//}
}

bool Doc::CheckMapCollision()
{
	return true;
}