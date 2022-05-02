#include "Cannon.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include "Background.h"
#include "ContentsEnum.h"
#include "Player.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineCollision.h>
#include <vector>
#include "Tomato.h"
#include "DieEffect.h"
#include "StarAttackEffect.h"
#include "AttackEffect.h"
#include "IceAttackEffect.h"
#include "FireAttackEffect.h"
#include "TransformEffect.h"
#include "SparkAttackEffect.h"
#include "RunEffect.h"
#include "GroundStarEffect.h"

Cannon::Cannon()
	:CanCol_(nullptr)
	,CannonRenderer_(nullptr)
	,CanRenderer_(nullptr)
	,PlayerRenderer_(nullptr)
	,Player_(nullptr)
	,TomatoRenderer_(nullptr)
{
}

Cannon::~Cannon()
{
}

void Cannon::Update()
{
	if (Player_->GetPosition().x >= GetMapSizeX() - 20)
	{
		GameEngine::GetInst().ChangeLevel("DanceStage");
	}

	if (true == CanRenderer_->IsAnimationName("CanStop") && true == CanRenderer_->IsEndAnimation())
	{
		Player_->SetGravity(0.0f);
		if (true != CannonRenderer_->IsAnimationName("None2") && false == CannonRenderer_->IsAnimationName("Cannon"))
		{
			CannonRenderer_->ChangeAnimation("Cannon");
		}

		if ((PrevPos_.x - Player_->GetPosition().x) > -1000)
		{
			PlayerRenderer_->ChangeAnimation("Die");
			PlayerRenderer_->GetActor()->On();
			Player_->SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 5000);
		}
	}

	if (true == CannonRenderer_->IsAnimationName("Cannon") && true == CannonRenderer_->IsEndAnimation())
	{
		CannonRenderer_->ChangeAnimation("None2");
	}

	if (true == CanRenderer_->IsAnimationName("CanMove") && true == CanRenderer_->IsEndAnimation() && true != CanRenderer_->IsAnimationName("CanStop"))
	{
		CanRenderer_->ChangeAnimation("CanStop");

	}

	if (CanCol_->CollisionCheck("KirbyCol",CollisionType::Rect,CollisionType::Rect) &&
		true != CanRenderer_->IsAnimationName("CanMove") &&
		true != CanRenderer_->IsAnimationName("CanStop"))
	{
		PrevPos_.x = Player_->GetPosition().x;
		PlayerRenderer_->GetActor()->Off();
		CanRenderer_->ChangeAnimation("CanMove");
	}
}


void Cannon::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	SetMapSizeX(768);
	SetMapSizeY(576);
	{
		Background* Cannon = CreateActor<Background>((int)ORDER::BACKGROUND);
		Cannon->CreateRenderer("Cannon.bmp");
		SetColMapImage("CannonColMap.bmp");
		ColMapImage_ = GetColMapImage();

	}

	{
		Background* Can = CreateActor<Background>((int)ORDER::BACKGROUND);
		CanRenderer_ = Can->CreateRenderer("can.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(0.0f, 30.0f));
		GameEngineImage* CanImage = CanRenderer_->GetImage();
		CanImage->CutCount(4, 2);
		CanRenderer_->CreateAnimation("can.bmp", "CanIdle", 0, 0, 0.08f, false);
		CanRenderer_->CreateAnimation("can.bmp", "CanMove", 0, 7, 0.08f, false);
		CanRenderer_->CreateAnimation("can.bmp", "CanStop", 0, 2, 0.08f, false);

		CanRenderer_->ChangeAnimation("CanIdle");
		CanCol_ = Can->CreateCollision("CanCol", float4(50.0f, 50.0f), float4(0.0f, 30.0f));

	}
	{
		Background* Tomato_ = CreateActor<Background>((int)ORDER::BACKGROUND);
		TomatoRenderer_ = Tomato_->CreateRenderer("Tomato.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(-5.0f, -235.0f));
		GameEngineImage* TomatoImage = TomatoRenderer_->GetImage();
		TomatoImage->CutCount(1, 1);
		TomatoRenderer_->CreateAnimation("Tomato.bmp", "Tomato", 0, 0, 0.1f, true);
		TomatoRenderer_->ChangeAnimation("Tomato");
	}

	{
		StarAttackEffect* StarAttackEffect_ = CreateActor<StarAttackEffect>((int)ORDER::EFFECT);
		AttackEffect* AttackEffect_ = CreateActor<AttackEffect>((int)ORDER::EFFECT);
		IceAttackEffect* IceAttackEffect_ = CreateActor<IceAttackEffect>((int)ORDER::EFFECT);
		FireAttackEffect* FireAttackEffect_ = CreateActor<FireAttackEffect>((int)ORDER::EFFECT);
		SparkAttackEffect* SparkAttackEffect_ = CreateActor<SparkAttackEffect>((int)ORDER::EFFECT);
		RunEffect* RunEffect_ = CreateActor<RunEffect>((int)ORDER::EFFECT);
		TransformEffect* TransformEffect_ = CreateActor<TransformEffect>((int)ORDER::EFFECT);
		GroundStarEffect* GroundStarEffect_ = CreateActor<GroundStarEffect>((int)ORDER::EFFECT);
		Player_ = CreateActor<Player>((int)ORDER::PLAYER);
		Player_->SetPosition(float4(384.0f, 0.0f));
		PlayerRenderer_ = Player_->GetRenderer();
		PlayerRenderer_->ChangeAnimation("JumpDownRight");
		
		Player_->SetStarAttackEffect(StarAttackEffect_);
		Player_->SetAttackEffect(AttackEffect_);
		Player_->SetIceAttackEffect(IceAttackEffect_);
		Player_->SetFireAttackEffect(FireAttackEffect_);
		Player_->SetSparkAttackEffect(SparkAttackEffect_);
		Player_->SetRunEffect(RunEffect_);
		Player_->SetTransformEffect(TransformEffect_);
		Player_->SetGroundStarEffect(GroundStarEffect_);



		Background* CannonEffect_ = CreateActor<Background>((int)ORDER::BACKGROUND);
		CannonRenderer_ = CannonEffect_->CreateRenderer("MonsterDie.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(0.0f, 20.0f));
		GameEngineImage* CannonImage = CannonRenderer_->GetImage();
		CannonImage->CutCount(10, 3);
		CannonRenderer_->CreateAnimation("MonsterDie.bmp", "Cannon", 14, 20, 0.03f, true);
		CannonRenderer_->CreateAnimation("MonsterDie.bmp", "None1", 14, 14, 0.03f, true);
		CannonRenderer_->CreateAnimation("MonsterDie.bmp", "None2", 14, 14, 0.03f, true);
		CannonRenderer_->ChangeAnimation("None1");
	}

	{

	}
}

void Cannon::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

void Cannon::Loading()
{
}
