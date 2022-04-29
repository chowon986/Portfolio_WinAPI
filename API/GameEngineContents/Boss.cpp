#include "Boss.h"
#include "Dedede.h"
#include "Player.h"
#include "BotUI.h"
#include "Background.h"
#include "ContentsEnum.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "StarAttackEffect.h"
#include "IceAttackEffect.h"
#include "AttackEffect.h"
#include "SparkAttackEffect.h"
#include "FireAttackEffect.h"
#include "RunEffect.h"

Boss::Boss()
{
}

Boss::~Boss()
{
}


void Boss::Loading()
{
}

void Boss::Update()
{
	SetCameraPos(Player_->GetPosition() - GameEngineWindow::GetInst().GetScale().Half());

	if (0 > GetCameraPos().x)
	{
		float4 CurCameraPos = GetCameraPos();
		CurCameraPos.x = 0;
		SetCameraPos(CurCameraPos);
	}

	if (0 > GetCameraPos().y)
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
		CurCameraPos.x = GetCameraPos().x - (GetCameraPos().x + CameraRectX - GetMapSizeX());
		SetCameraPos(CurCameraPos);
	}

	if (GetMapSizeY() <= GetCameraPos().y + CameraRectY)
	{
		float4 CurCameraPos = GetCameraPos();
		CurCameraPos.y = GetCameraPos().y - (GetCameraPos().y + CameraRectY - GetMapSizeY());
		SetCameraPos(CurCameraPos);
	}
}

void Boss::LevelChangeStart()
{
	SetColMapImage("BossColMap.bmp");
	ColMapImage_ = GetColMapImage();

	SetMapSizeX(768);
	SetMapSizeY(576);

	{
		// Background
		//BossLevelEnd_ = CreateActor<Background>((int)ORDER::BACKGROUND);
		//BossLevelEndRenderer_ = BossLevelEnd_->CreateRenderer("BossLevelEnd.bmp");
		//BossLevelEndImage_ = BossLevelEndRenderer_->GetImage();
		//BossLevelEndImage_->CutCount(6, 2);
		//BossLevelEndRenderer_->CreateAnimation("BossLevelEnd.bmp", "End", 0, 11, 0.1f, true);

		BossLevelStart_ = CreateActor<Background>((int)ORDER::BACKGROUND);
		BossLevelStartRenderer_ = BossLevelStart_->CreateRenderer("BossLevelStart.bmp");
		BossLevelStartImage_ = BossLevelStartRenderer_->GetImage();
		BossLevelStartImage_->CutCount(6, 2);
		BossLevelStartRenderer_->CreateAnimation("BossLevelStart.bmp", "Start", 0, 11, 0.1f, true);

		BossLevelStartRenderer_->ChangeAnimation("Start");
	} 

	{
		Player_ = CreateActor<Player>((int)ORDER::PLAYER);
		Player_->SetPosition(float4(600.0f, 400.0f));
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
		// Boss
		Dedede* Dedede_ = CreateActor<Dedede>((int)ORDER::MONSTER);
		Dedede_->SetPosition(float4(640.0f, 440.0f));
	}

}
