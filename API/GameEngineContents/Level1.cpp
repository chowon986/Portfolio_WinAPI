#include "Level1.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Background.h"
#include "Player.h"
#include "Monster.h"
#include "Waddledee.h"
#include "Monster1.h"
#include "Sparky.h"
#include "BotUI.h"
#include "ContentsEnum.h"
#include "GameEngine/GameEngineImage.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageManager.h>
#include "AbandonEffect.h"
#include "StarAttackEffect.h"
#include "AttackEffect.h"
#include "IceAttackEffect.h"
#include "FireAttackEffect.h"
#include "SparkAttackEffect.h"
#include "DieEffect.h"
#include "RunEffect.h"
#include "GameEngineBase/GameEngineSound.h"
#include "TransformEffect.h"
#include "GroundStarEffect.h"

Level1::Level1()
	: Player_(nullptr)
	, PlayerStatus_(nullptr)
	, ColMapImage_(nullptr)
	, DoorCol1_2(nullptr)
{

}

Level1::~Level1()
{
}


void Level1::Loading()
{

}

void Level1::DelayUpdate()
{
	SetCameraPos(Player_->GetPosition() - GameEngineWindow::GetInst().GetScale().Half());

	if (0 >= GetCameraPos().x)
	{
		float4 CurCameraPos = GetCameraPos();
		CurCameraPos.x = 0;
		SetCameraPos(CurCameraPos);
	}

	if (0 >= GetCameraPos().y)
	{
		float4 CurCameraPos = GetCameraPos();
		CurCameraPos.y = 0;
		SetCameraPos(CurCameraPos);
	}

	float CameraRectX = 768;
	float CameraRectY = 576;

	if (GetMapSizeX() <= GetCameraPos().x + CameraRectX)
	{
		float4 CurCameraPos = GetCameraPos();
		CurCameraPos.x = static_cast<int>(GetCameraPos().ix() - (GetCameraPos().ix() + CameraRectX - GetMapSizeX()));
		SetCameraPos(CurCameraPos);
	}

	if (GetMapSizeY() <= GetCameraPos().y + CameraRectY)
	{
		float4 CurCameraPos = GetCameraPos();
		CurCameraPos.y = static_cast<int>(GetCameraPos().iy() - (GetCameraPos().iy() + CameraRectY - GetMapSizeY()));
		SetCameraPos(CurCameraPos);
	}

	if (true == GameEngineInput::GetInst()->IsDown("Collision"))
	{
		IsDebugModeOn();
	}
}

void Level1::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	GameEngineLevelBase::LevelChangeStart(_PrevLevel);
	SetMapSizeX(4608);
	SetMapSizeY(576);

	BgmPlayer = GameEngineSound::SoundPlayControl("Stage1.mp3");
	SetColMapImage("Stage1ColMap.bmp");
	ColMapImage_ = GetColMapImage();


	if (ColMapImage_ == nullptr)
	{
		MsgBoxAssert("�浹�� �̹����� ã�� ���߽��ϴ�.")
	}

	{
		Background* Stage1 = CreateActor<Background>((int)ORDER::BACKGROUND);
		Stage1->CreateRenderer("Stage1.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(1920.0f, 0.0f));
	}

	{
		Background* Door = CreateActor<Background>((int)ORDER::BACKGROUND);
		Door->CreateRenderer("Door.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(4153.0f, 60.0f));
		DoorCol1_2 = Door->CreateCollision("DoorCol1_2", float4(44.0f, 64.0f), float4(4153.0f,60.0f));

		Background* DoorStar = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* DoorStarRenderer = DoorStar->CreateRenderer("DoorStar.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(4153.0f, 10.0f));
		GameEngineImage* DoorStarImage = DoorStarRenderer->GetImage();
		DoorStarImage->CutCount(6, 2);
		DoorStarRenderer->CreateAnimation("DoorStar.bmp", "DoorStar", 0, 11, 0.05f, true);
		DoorStarRenderer->ChangeAnimation("DoorStar");
	}
	{
		Background* Grass1 = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* Grass1Renderer = Grass1->CreateRenderer("grass1.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(245.0f, 150.0f));
		GameEngineImage* Grass1Image = Grass1Renderer->GetImage();
		Grass1Image->CutCount(2, 2);
		Grass1Renderer->CreateAnimation("grass1.bmp", "grass1", 0, 3, 0.5f, true);
		Grass1Renderer->ChangeAnimation("grass1");
	}

	{
		Background* Grass2 = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* Grass2Renderer = Grass2->CreateRenderer("grass2.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(2078.0f, -45.0f));
		GameEngineImage* Grass2Image = Grass2Renderer->GetImage();
		Grass2Image->CutCount(2, 2);
		Grass2Renderer->CreateAnimation("grass2.bmp", "grass2", 0, 3, 0.5f, true);
		Grass2Renderer->ChangeAnimation("grass2");
	}

	{
		Background* Grass3 = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* Grass3Renderer = Grass3->CreateRenderer("grass3.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(3545.0f, 97.0f));
		GameEngineImage* Grass3Image = Grass3Renderer->GetImage();
		Grass3Image->CutCount(2, 2);
		Grass3Renderer->CreateAnimation("grass3.bmp", "grass3", 0, 3, 0.5f, true);
		Grass3Renderer->ChangeAnimation("grass3");
	}

	{
		AbandonEffect* AbandonEffect_ = CreateActor<AbandonEffect>((int)ORDER::EFFECT);
		StarAttackEffect* StarAttackEffect_ = CreateActor<StarAttackEffect>((int)ORDER::EFFECT);
		AttackEffect* AttackEffect_ = CreateActor<AttackEffect>((int)ORDER::EFFECT);
		IceAttackEffect* IceAttackEffect_ = CreateActor<IceAttackEffect>((int)ORDER::EFFECT);
		FireAttackEffect* FireAttackEffect_ = CreateActor<FireAttackEffect>((int)ORDER::EFFECT);
		SparkAttackEffect* SparkAttackEffect_ = CreateActor<SparkAttackEffect>((int)ORDER::EFFECT);
		RunEffect* RunEffect_ = CreateActor<RunEffect>((int)ORDER::EFFECT);
		TransformEffect* TransformEffect_ = CreateActor<TransformEffect>((int)ORDER::EFFECT);
		GroundStarEffect* GroundStarEffect_ = CreateActor<GroundStarEffect>((int)ORDER::EFFECT);

		Player_ = CreateActor<Player>((int)ORDER::PLAYER);
		Player_->SetPosition(float4(205.0f, 436.0f));
		Player_->SetMapStartPos(float4(205.0f, 436.0f));
		PlayerStatus_ = CreateActor<BotUI>((int)ORDER::BOTUI);
		PlayerStatus_->SetPlayer(Player_);
		Player_->SetStarAttackEffect(StarAttackEffect_);
		Player_->SetAttackEffect(AttackEffect_);
		Player_->SetIceAttackEffect(IceAttackEffect_);
		Player_->SetFireAttackEffect(FireAttackEffect_);
		Player_->SetSparkAttackEffect(SparkAttackEffect_);
		Player_->SetRunEffect(RunEffect_);
		Player_->SetTransformEffect(TransformEffect_);
		Player_->SetGroundStarEffect(GroundStarEffect_);
		Player_->SetAbandonEffect(AbandonEffect_);
	}

	{
		Waddledee* Waddledee_ = CreateActor<Waddledee>((int)ORDER::MONSTER);
		Waddledee_->SetPosition(float4(1200.0f, 430.0f));

		DieEffect* DieEffect_ = CreateActor<DieEffect>((int)ORDER::EFFECT);
		Waddledee_->SetDieEffect(DieEffect_);
	}

	{
		Monster1* Monster1_ = CreateActor<Monster1>((int)ORDER::MONSTER);
		Monster1_->SetPosition(float4(2840.0f, 377.0f));

		DieEffect* DieEffect_ = CreateActor<DieEffect>((int)ORDER::EFFECT);
		Monster1_->SetDieEffect(DieEffect_);
	}

	{
		Monster* Sparky_ = CreateActor<Sparky>((int)ORDER::MONSTER);
		Sparky_->SetPosition(float4(3780.0f, 380.0f));

		DieEffect* DieEffect_ = CreateActor<DieEffect>((int)ORDER::EFFECT);
		Sparky_->SetDieEffect(DieEffect_);
	}
}
