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
#include "AbandonEffect.h"
#include "GameEngineBase/GameEngineSound.h"

Cannon::Cannon()
	:CanCol_(nullptr)
	, CannonRenderer_(nullptr)
	, CanRenderer_(nullptr)
	, PlayerRenderer_(nullptr)
	, Player_(nullptr)
	, TomatoRenderer_(nullptr)
	, Rotation_(false)
	, Index_(-1)
{
}

Cannon::~Cannon()
{
}

void Cannon::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	GameEngineLevelBase::LevelChangeStart(_PrevLevel);

	DelayTime_ = 1.0f;

	BgmPlayer_ = GameEngineSound::SoundPlayControl("Cannon.mp3");
	SetColMapImage("Cannon.bmp");
	ColMapImage_ = GetColMapImage();

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
		CanRenderer_->CreateAnimation("can.bmp", "Can0", 0, 0, 0.08f, false);
		CanRenderer_->CreateAnimation("can.bmp", "Can1", 1, 1, 0.08f, false);
		CanRenderer_->CreateAnimation("can.bmp", "Can2", 2, 2, 0.08f, false);
		CanRenderer_->CreateAnimation("can.bmp", "Can3", 3, 3, 0.08f, false);
		CanRenderer_->CreateAnimation("can.bmp", "Can4", 4, 4, 0.08f, false);
		CanRenderer_->CreateAnimation("can.bmp", "Can5", 5, 5, 0.08f, false);
		CanRenderer_->CreateAnimation("can.bmp", "Can6", 6, 6, 0.08f, false);
		CanRenderer_->CreateAnimation("can.bmp", "Can7", 7, 7, 0.08f, false);

		CanRenderer_->ChangeAnimation("Can0");
		CanCol_ = Can->CreateCollision("CanCol", float4(50.0f, 10.0f), float4(0.0f, 30.0f));

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
		AbandonEffect* AbandonEffect_ = CreateActor<AbandonEffect>((int)ORDER::EFFECT);
		Player_->SetAbandonEffect(AbandonEffect_);
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
		Player_->SetDelayTime(DelayTime_);


		//Background* CannonEffect_ = CreateActor<Background>((int)ORDER::BACKGROUND);
		//CannonRenderer_ = CannonEffect_->CreateRenderer("MonsterDie.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(0.0f, 20.0f));
		//GameEngineImage* CannonImage = CannonRenderer_->GetImage();
		//CannonImage->CutCount(10, 3);
		//CannonRenderer_->CreateAnimation("MonsterDie.bmp", "Cannon", 14, 20, 0.03f, true);
		//CannonRenderer_->CreateAnimation("MonsterDie.bmp", "None1", 14, 14, 0.03f, true);
		//CannonRenderer_->CreateAnimation("MonsterDie.bmp", "None2", 14, 14, 0.03f, true);
		//CannonRenderer_->ChangeAnimation("None1");
	}

	GameEngineInput::GetInst()->CreateKey("Stop", VK_SPACE);
}

void Cannon::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BgmPlayer_.Stop();
}

void Cannon::DelayUpdate()
{	
	if (-1 != Index_ && RGB(152,184,16) == ColMapImage_->GetImagePixel(Player_->GetPosition()))
	{
		GameEngine::GetInst().ChangeLevel("DanceStage");
	}


	// Ŀ��� �ε�����
	if (-1 == Index_ && CanCol_->CollisionCheck("KirbyCol", CollisionType::Rect, CollisionType::Rect))
	{
		Rotation_ = true;
		PrevPos_.x = Player_->GetPosition().x;
		PlayerRenderer_->GetActor()->Off();
	}

	if (true == Rotation_)
	{
		Time_ += GameEngineTime::GetDeltaTime(); // 0.1
		int Index = (int)(Time_ * 12) % 8;
		std::string AnimationName = "Can" + std::to_string(Index);
		CanRenderer_->ChangeAnimation(AnimationName);

		if (true == GameEngineInput::GetInst()->IsDown("Stop"))
		{
			Rotation_ = false;
			Index_ = Index;
			Player_->SetGravity(0.0f);
		}
	}

	float deltaMove = GameEngineTime::GetDeltaTime() * 500;
	switch (Index_)
	{
	case 0:		
		Player_->On();
		Player_->SetMove(float4(0, -deltaMove));
		break;
	case 1:
		Player_->On();
		Player_->SetMove(float4(deltaMove, -deltaMove));
		break;
	case 2:
		Player_->On();
		Player_->SetMove(float4(deltaMove, 0));
		break;
	case 3:
		Player_->On();
		Player_->SetMove(float4(deltaMove, deltaMove));
		break;
	case 4:
		Player_->On();
		Player_->SetMove(float4(0, deltaMove));
		break;
	case 5:
		Player_->On();
		Player_->SetMove(float4(-deltaMove, deltaMove));
		break;
	case 6:
		Player_->On();
		Player_->SetMove(float4(-deltaMove, 0));
		break;
	case 7:
		Player_->On();
		Player_->SetMove(float4(-deltaMove, -deltaMove));
		break;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Collision"))
	{
		IsDebugModeOn();
	}
}

void Cannon::Loading()
{

}
