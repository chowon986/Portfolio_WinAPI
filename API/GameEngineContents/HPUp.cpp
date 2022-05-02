#include "HPUp.h"
#include <GameEngine/GameEngineCollision.h>
#include "Player.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineActor.h>

HPUp::HPUp()
	: HPUpCol_(nullptr)
	, HPUpRenderer_(nullptr)
{
}

HPUp::~HPUp()
{
}

void HPUp::Start()
{
	HPUpRenderer_ = CreateRenderer("HPUp.bmp");
	HPUpCol_ = CreateCollision("Item", float4(40.0f, 40.0f), float4(0.0f, 0.0f));
}

void HPUp::Update()
{
	std::vector<GameEngineCollision*> ColResult;

	if (true == HPUpCol_->CollisionResult("KirbyCol", ColResult, CollisionType::Rect, CollisionType::Rect))
	{
		for (GameEngineCollision* Collision : ColResult)
		{
			GameEngineActor* ColActor = Collision->GetActor();
			Player* Kirby = dynamic_cast<Player*>(ColActor); // dynamic_cast -> ��ȯ �����ϸ� player, �����ϸ� null�� ��
			if (nullptr != Kirby)
			{
				Kirby->SetHPCount(Kirby->GetHPCount() + 1);
				Death();
				GameEngineSound::SoundPlayOneShot("EatItem.wav", 1);
			}
		}
	}
}
