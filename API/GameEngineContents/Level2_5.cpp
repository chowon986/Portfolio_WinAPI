#include "Level2_5.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Background.h"
#include "Player.h"
#include "Monster.h"
#include "Monster1.h"
#include "Sword.h"
#include "Tiktik.h"
#include "BotUI.h"
#include "Sparky.h"
#include "TreasureChest.h"
#include "ContentsEnum.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include "StarAttackEffect.h"
#include "IceAttackEffect.h"
#include "AttackEffect.h"
#include "SparkAttackEffect.h"
#include "FireAttackEffect.h"
#include "RunEffect.h"
#include <GameEngine/GameEngineImage.h>

Level2_5::Level2_5()
	: Player_(nullptr)
	, Cannon_(nullptr)
	, PlayerStatus_(nullptr)
{
}

Level2_5::~Level2_5()
{
}


void Level2_5::Loading()
{
}

void Level2_5::Update()
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
}

void Level2_5::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	SetMapSizeX(5280);
	SetMapSizeY(576);

	SetColMapImage("Stage2_5ColMap.bmp");
	ColMapImage_ = GetColMapImage();

	if (ColMapImage_ == nullptr)
	{
		MsgBoxAssert("충돌맵 이미지를 찾지 못했습니다.")
	}

	{
		Background* Stage2_5 = CreateActor<Background>((int)ORDER::BACKGROUND);
		Stage2_5->CreateRenderer("Stage2_5.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(2256.0f, 0.0f));
	}

	{
		Player_ = CreateActor<Player>((int)ORDER::PLAYER);
		Player_->SetPosition(float4(4000.0f, 100.0f));
		PlayerStatus_ = CreateActor<BotUI>((int)ORDER::BOTUI);
		PlayerStatus_->SetPlayer(Player_);

		StarAttackEffect* StarAttackEffect_ = CreateActor<StarAttackEffect>((int)ORDER::EFFECT);
		AttackEffect* AttackEffect_ = CreateActor<AttackEffect>((int)ORDER::EFFECT);
		IceAttackEffect* IceAttackEffect_ = CreateActor<IceAttackEffect>((int)ORDER::EFFECT);
		FireAttackEffect* FireAttackEffect_ = CreateActor<FireAttackEffect>((int)ORDER::EFFECT);
		SparkAttackEffect* SparkAttackEffect_ = CreateActor<SparkAttackEffect>((int)ORDER::EFFECT);
		RunEffect* RunEffect_ = CreateActor<RunEffect>((int)ORDER::EFFECT);

		Player_->SetStarAttackEffect(StarAttackEffect_);
		Player_->SetAttackEffect(AttackEffect_);
		Player_->SetIceAttackEffect(IceAttackEffect_);
		Player_->SetFireAttackEffect(FireAttackEffect_);
		Player_->SetSparkAttackEffect(SparkAttackEffect_);
		Player_->SetRunEffect(RunEffect_);
	}

	{
		TreasureChest* TreasureChest_ = CreateActor<TreasureChest>((int)ORDER::MONSTER);
		TreasureChest_->SetPosition(float4(375.0f, 175.0f));
	}

	{
		Monster1* Monster1_ = CreateActor<Monster1>((int)ORDER::MONSTER);
		Monster1_->SetPosition(float4(1200.0f, 440.0f));
	}

	{
		Sparky* Sparky_ = CreateActor<Sparky>((int)ORDER::MONSTER);
		Sparky_->SetPosition(float4(2500.0f, 390.0f));
	}

	{
		Tiktik* Tiktik_ = CreateActor<Tiktik>((int)ORDER::MONSTER);
		Tiktik_->SetPosition(float4(4000.0f, 440.0f));
	}

	Background* Water1 = CreateActor<Background>((int)ORDER::BACKGROUND);
	GameEngineRenderer* Water1Renderer = Water1->CreateRenderer("Water1.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(410.0f, 340.0f));
	GameEngineImage* Water1Image = Water1Renderer->GetImage();
	Water1Image->CutCount(4, 1);
	Water1Renderer->CreateAnimation("Water1.bmp", "Water1", 0, 3, 0.5f, true);
	Water1Renderer->ChangeAnimation("Water1");

	Background* Water2 = CreateActor<Background>((int)ORDER::BACKGROUND);
	GameEngineRenderer* Water2Renderer = Water2->CreateRenderer("Water1.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(700.0f, 340.0f));
	GameEngineImage* Water2Image = Water2Renderer->GetImage();
	Water2Image->CutCount(4, 1);
	Water2Renderer->CreateAnimation("Water1.bmp", "Water1", 0, 3, 0.5f, true);
	Water2Renderer->ChangeAnimation("Water1");

	Background* Water3 = CreateActor<Background>((int)ORDER::BACKGROUND);
	GameEngineRenderer* Water3Renderer = Water3->CreateRenderer("Water2.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(1323.0f, 340.0f));
	GameEngineImage* Water3Image = Water3Renderer->GetImage();
	Water3Image->CutCount(4, 1);
	Water3Renderer->CreateAnimation("Water2.bmp", "Water2", 0, 3, 0.5f, true);
	Water3Renderer->ChangeAnimation("Water2");

	Background* Water4 = CreateActor<Background>((int)ORDER::BACKGROUND);
	GameEngineRenderer* Water4Renderer = Water4->CreateRenderer("Water3.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(4535.0f, 340.0f));
	GameEngineImage* Water4Image = Water4Renderer->GetImage();
	Water4Image->CutCount(4, 1);
	Water4Renderer->CreateAnimation("Water3.bmp", "Water3", 0, 3, 0.5f, true);
	Water4Renderer->ChangeAnimation("Water3");

	Background* Water5 = CreateActor<Background>((int)ORDER::BACKGROUND);
	GameEngineRenderer* Water5Renderer = Water5->CreateRenderer("Water3.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(4680.0f, 340.0f));
	GameEngineImage* Water5Image = Water5Renderer->GetImage();
	Water5Image->CutCount(4, 1);
	Water5Renderer->CreateAnimation("Water3.bmp", "Water3", 0, 3, 0.5f, true);
	Water5Renderer->ChangeAnimation("Water3");


	Background* Door = CreateActor<Background>((int)ORDER::BACKGROUND);
	GameEngineRenderer* DoorRenderer = Door->CreateRenderer("BigDoor2.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(4756.0f, -137.0f));
	Cannon_ = Door->CreateCollision("Cannon", float4(90.0f, 70.0f), float4(4756.0f, -137.0f));

	Background* DoorStar = CreateActor<Background>((int)ORDER::BACKGROUND);
	GameEngineRenderer* DoorStarRenderer = DoorStar->CreateRenderer("BigDoorStar.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(4750.0f, -170.0f));
	GameEngineImage* DoorStarImage = DoorStarRenderer->GetImage();
	DoorStarImage->CutCount(6, 2);
	DoorStarRenderer->CreateAnimation("BigDoorStar.bmp", "BigDoorStar", 0, 11, 0.05f, true);
	DoorStarRenderer->ChangeAnimation("BigDoorStar");
}
