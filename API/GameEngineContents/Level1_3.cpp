#include "Level1_3.h"
#include <GameEngine/GameEngine.h>
#include<GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "ContentsEnum.h"
#include "Background.h"
#include "BotUI.h"
#include "Player.h"
#include "Monster.h"
#include "HPUp.h"
#include "StarAttackEffect.h"
#include "IceAttackEffect.h"
#include "AttackEffect.h"
#include "SparkAttackEffect.h"
#include "FireAttackEffect.h"
#include "RunEffect.h"
#include "AbandonEffect.h"
#include "TransformEffect.h"



Level1_3::Level1_3()
	: Player_(nullptr)
{
}

Level1_3::~Level1_3()
{
}


void Level1_3::Loading()
{
}

void Level1_3::DelayUpdate()
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

void Level1_3::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	GameEngineLevelBase::LevelChangeStart(_PrevLevel);
	SetMapSizeX(768);
	SetMapSizeY(1152);
	SetColMapImage("Stage1_3ColMap.bmp");
	ColMapImage_ = GetColMapImage();

	if (ColMapImage_ == nullptr)
	{
		MsgBoxAssert("충돌맵 이미지를 찾지 못했습니다.")
	}

	{
		Background* Stage1_3 = CreateActor<Background>((int)ORDER::BACKGROUND);
		Stage1_3->CreateRenderer("Stage1_3.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(0.0f,280.0f));
	}

	{
		StarAttackEffect* StarAttackEffect_ = CreateActor<StarAttackEffect>((int)ORDER::EFFECT);
		AttackEffect* AttackEffect_ = CreateActor<AttackEffect>((int)ORDER::EFFECT);
		IceAttackEffect* IceAttackEffect_ = CreateActor<IceAttackEffect>((int)ORDER::EFFECT);
		FireAttackEffect* FireAttackEffect_ = CreateActor<FireAttackEffect>((int)ORDER::EFFECT);
		SparkAttackEffect* SparkAttackEffect_ = CreateActor<SparkAttackEffect>((int)ORDER::EFFECT);
		RunEffect* RunEffect_ = CreateActor<RunEffect>((int)ORDER::EFFECT);
		AbandonEffect* AbandonEffect_ = CreateActor<AbandonEffect>((int)ORDER::EFFECT);
		TransformEffect* TransformEffect_ = CreateActor<TransformEffect>((int)ORDER::EFFECT);
		Player_ = CreateActor<Player>((int)ORDER::PLAYER);
		Player_->SetAbandonEffect(AbandonEffect_);
		Player_->SetPosition(float4(45, 960));
		PlayerStatus_ = CreateActor<BotUI>((int)ORDER::BOTUI);
		PlayerStatus_->SetPlayer(Player_);
		Player_->SetTransformEffect(TransformEffect_);
		Player_->SetStarAttackEffect(StarAttackEffect_);
		Player_->SetAttackEffect(AttackEffect_);
		Player_->SetIceAttackEffect(IceAttackEffect_);
		Player_->SetFireAttackEffect(FireAttackEffect_);
		Player_->SetSparkAttackEffect(SparkAttackEffect_);
		Player_->SetRunEffect(RunEffect_);
	}

	{
		// 아이템 생성
		HPUp* HPUp_ = CreateActor<HPUp>((int)ORDER::ITEM);
		HPUp_->SetPosition(float4(145.0f, 400.0f));
	}

	{
		Background* Door = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* DoorRenderer = Door->CreateRenderer("Door.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(312.0f, -36.0f));
		DoorCol1_4 = Door->CreateCollision("DoorCol1_4", float4(48.0f, 64.0f), float4(312.0f, -36.0f));

		Background* DoorStar = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* DoorStarRenderer = DoorStar->CreateRenderer("DoorStar.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(312.0f, -80.0f));
		GameEngineImage* DoorStarImage = DoorStarRenderer->GetImage();
		DoorStarImage->CutCount(6, 2);
		DoorStarRenderer->CreateAnimation("DoorStar.bmp", "DoorStar", 0, 11, 0.05f, true);
		DoorStarRenderer->ChangeAnimation("DoorStar");
	}
}