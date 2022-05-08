#include "Level3.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include "Player.h"
#include "BotUI.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "Background.h"
#include "Monster.h"
#include "Monster1.h"
#include "Waddledee.h"
#include "BigWaddledee.h"
#include "ContentsEnum.h"
#include "StarAttackEffect.h"
#include "IceAttackEffect.h"
#include "AttackEffect.h"
#include "SparkAttackEffect.h"
#include "FireAttackEffect.h"
#include "RunEffect.h"
#include "AbandonEffect.h"
#include "TransformEffect.h"
#include <GameEngineBase/GameEngineSound.h>


Level3::Level3()
	: Player_(nullptr)
	, PlayerStatus_(nullptr)
	, Boss(nullptr)
{
}

Level3::~Level3()
{
}


void Level3::Loading()
{

}

void Level3::DelayUpdate()
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

void Level3::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	LEVEL_BGM = GameEngineSound::SoundPlayControl("Stage3.mp3");
	GameEngineLevelBase::LevelChangeStart(_PrevLevel);
	SetMapSizeX(768);
	SetMapSizeY(576);

	SetColMapImage("Stage3ColMap.bmp");
	ColMapImage_ = GetColMapImage();

	if (ColMapImage_ == nullptr)
	{
		MsgBoxAssert("�浹�� �̹����� ã�� ���߽��ϴ�.")
	}

	{
		Background* Stage3 = CreateActor<Background>((int)ORDER::BACKGROUND);
		Stage3->CreateRenderer("Stage3.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(0.0f, 0.0f));
		Stage3->CreateCollision("Boss", float4(50.0f, 50.0f), float4(345.0f, 110.0f));
	}

	{
		Player_ = CreateActor<Player>((int)ORDER::PLAYER);
		Player_->SetPosition(float4(50, 320));
		PlayerStatus_ = CreateActor<BotUI>((int)ORDER::BOTUI);
		PlayerStatus_->SetPlayer(Player_);

		StarAttackEffect* StarAttackEffect_ = CreateActor<StarAttackEffect>((int)ORDER::EFFECT);
		AttackEffect* AttackEffect_ = CreateActor<AttackEffect>((int)ORDER::EFFECT);
		IceAttackEffect* IceAttackEffect_ = CreateActor<IceAttackEffect>((int)ORDER::EFFECT);
		FireAttackEffect* FireAttackEffect_ = CreateActor<FireAttackEffect>((int)ORDER::EFFECT);
		SparkAttackEffect* SparkAttackEffect_ = CreateActor<SparkAttackEffect>((int)ORDER::EFFECT);
		RunEffect* RunEffect_ = CreateActor<RunEffect>((int)ORDER::EFFECT);
		AbandonEffect* AbandonEffect_ = CreateActor<AbandonEffect>((int)ORDER::EFFECT);
		Player_->SetAbandonEffect(AbandonEffect_);
		Player_->SetStarAttackEffect(StarAttackEffect_);
		Player_->SetAttackEffect(AttackEffect_);
		Player_->SetIceAttackEffect(IceAttackEffect_);
		Player_->SetFireAttackEffect(FireAttackEffect_);
		Player_->SetSparkAttackEffect(SparkAttackEffect_);
		Player_->SetRunEffect(RunEffect_);
	}


}

void Level3::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
	LEVEL_BGM.Stop();
}
