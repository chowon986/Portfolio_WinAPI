#include "IceItem.h"
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineSound.h>

IceItem::IceItem()
{
}

IceItem::~IceItem()
{
}

void IceItem::Start()
{
	IceItemRenderer_ = CreateRenderer("IceItem.bmp");
	GameEngineImage* IceImage = IceItemRenderer_->GetImage();
	IceImage->CutCount(2, 1);
	IceItemRenderer_->CreateAnimation("IceItem.bmp", "IceItem", 0, 1, 0.5f);
	IceItemRenderer_->ChangeAnimation("IceItem");
	IceItemCol_ = CreateCollision("Item", float4(40.0f, 40.0f), float4(0.0f, 0.0f));
}

void IceItem::Update()
{
	std::vector <GameEngineCollision*> ColResult;
	if (true == IceItemCol_->CollisionResult("KirbyCol", ColResult, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : ColResult)
		{
			GameEngineActor* Actor = Collision->GetActor();
			Player* Kirby = dynamic_cast<Player*>(Actor);
			if (nullptr != Kirby)
			{
				Kirby->SetKirbyClass(KirbyClass::ICE);
				GameEngineSound::SoundPlayOneShot("EatItem.wav", 0);
				Death();
			}
		}
	}
}
