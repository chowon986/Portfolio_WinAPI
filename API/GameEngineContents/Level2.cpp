#include "Level2.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Background.h"
#include "Player.h"
#include "Monster.h"
#include "BotUI.h"
#include "ContentsEnum.h"
#include "GameEngine/GameEngineImage.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImageManager.h>
#include "StarAttackEffect.h"
#include "IceAttackEffect.h"
#include "AttackEffect.h"
#include "SparkAttackEffect.h"
#include "FireAttackEffect.h"
#include "RunEffect.h"

Level2::Level2()
	: Player_(nullptr)

{
}

Level2::~Level2()
{
}


void Level2::Loading()
{
}

void Level2::Update()
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

void Level2::LevelChangeStart()
{
	SetMapSizeX(1536);
	SetMapSizeY(576);

	// 이미지 문제
	SetColMapImage("Stage2ColMap.bmp");
	ColMapImage_ = GetColMapImage();

	if (ColMapImage_ == nullptr)
	{
		MsgBoxAssert("충돌맵 이미지를 찾지 못했습니다.")
	}

	{
		Background* Stage2 = CreateActor<Background>((int)ORDER::BACKGROUND);
		Stage2->CreateRenderer("Stage2_1.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER,float4(384.0f,0.0f));
	}

	{
		Player_ = CreateActor<Player>((int)ORDER::PLAYER);
		Player_->SetPosition(float4(45, 320));
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

	Monster* SwrodItem = CreateActor<Monster>((int)ORDER::MONSTER);
	GameEngineRenderer* SwrodItemRenderer = SwrodItem->CreateRenderer("SwordItem3.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(958.0f, 330.0f));
	GameEngineImage* SwrodItemImage = SwrodItemRenderer->GetImage();
	SwrodItemImage->CutCount(2, 1);
	SwrodItemRenderer->CreateAnimation("SwordItem3.bmp", "SwordItem", 0, 1, 0.5f, true);
	SwrodItemRenderer->ChangeAnimation("SwordItem");

	{
		Background* Door = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* DoorRenderer = Door->CreateRenderer("Door.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(1078.0f, 70.0f));
		DoorCol2_2 = Door->CreateCollision("DoorCol2_2", float4(48.0f, 64.0f), float4(1078.0f, 70.0f));

		Background* DoorStar = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* DoorStarRenderer = DoorStar->CreateRenderer("DoorStar.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(1078.0f, 20.0f));
		GameEngineImage* DoorStarImage = DoorStarRenderer->GetImage();
		DoorStarImage->CutCount(6, 2);
		DoorStarRenderer->CreateAnimation("DoorStar.bmp", "DoorStar", 0, 11, 0.05f, true);
		DoorStarRenderer->ChangeAnimation("DoorStar");
	}
}

	////////////////////////////////
	// 1. bomb
	// 2. waddledi
	// 3. grass -> 구현 여부 정하기
	// 4. bomb
	// 5. bigwaddledi
	// 6. bomb
	//////////////////////////////
	// 1. hpup
	//////////////////////////////
	// 7. moon
	// 8. monster1
	// 9. bigwaddledi
	///////////////////////
	// 1. waddledi
	// 2. monster1
	// 3. fireitem
	// 4. 얼음 쏘는애
	/////////////////////
	// monster3 (악마같이 생긴애)
	// monster3
	// monster3
	/////////////////////
	// 1. bigbomb
	// 2. bigbomb + box
	// 3. animal
	// 4. hpup
	// 5. waddledi
	// 6. animal
	// 7. treasurechest
	// 8. bigwaddledi
	// 9. bigbomb
	///////////////////////////
	// big treasurechest
	// 쥐들
	// monster2던가 그 파란색
	// waddledoo
	//////////////////////////

	//////////////////////////
	// 1. warpstar
	/////////////////////////
	// pengy
	// cherry
	//////////////////////////
	// boss

