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

Level2::Level2()
	: Player_(nullptr)
	, MapSizeX_(1536)
	, MapSizeY_(573)
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

	if (MapSizeX_ <= GetCameraPos().x + CameraRectX)
	{
		float4 CurCameraPos = GetCameraPos();
		CurCameraPos.x = GetCameraPos().x - (GetCameraPos().x + CameraRectX - MapSizeX_);
		SetCameraPos(CurCameraPos);
	}

	if (MapSizeY_ <= GetCameraPos().y + CameraRectY)
	{
		float4 CurCameraPos = GetCameraPos();
		CurCameraPos.y = GetCameraPos().y - (GetCameraPos().y + CameraRectY - MapSizeY_);
		SetCameraPos(CurCameraPos);
	}
}

void Level2::LevelChangeStart()
{
	// 이미지 문제
	SetColMapImage("Stage2ColMap.bmp");
	ColMapImage_ = GetColMapImage();

	if (ColMapImage_ == nullptr)
	{
		MsgBoxAssert("충돌맵 이미지를 찾지 못했습니다.")
	}

	{
		Background* Stage2 = CreateActor<Background>((int)ORDER::BACKGROUND);
		Stage2->CreateRenderer("Stage2.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER,float4(384.0f,0.0f));
	}

	{
		Player_ = CreateActor<Player>((int)ORDER::PLAYER);
		Player_->SetPosition(float4(45, 320));
		PlayerUI_ = CreateActor<BotUI>((int)ORDER::BOTUI);
	}

	Monster* SwrodItem = CreateActor<Monster>((int)ORDER::MONSTER);
	GameEngineRenderer* SwrodItemRenderer = SwrodItem->CreateRenderer("SwordItem3.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(958.0f, 330.0f));
	GameEngineImage* SwrodItemImage = SwrodItemRenderer->GetImage();
	SwrodItemImage->CutCount(2, 1);
	SwrodItemRenderer->CreateAnimation("SwordItem3.bmp", "SwordItem", 0, 1, 0.5f, true);
	SwrodItemRenderer->ChangeAnimation("SwordItem");

	{
		// Door won't work -> need to chk
		Background* Door = CreateActor<Background>((int)ORDER::BACKGROUND);
		DoorCol2_2 = Door->CreateCollision("DoorCol2_2", float4(48.0f, 64.0f), float4(1078.0f, 70.0f));
	}
}

float Level2::GetMapSizeY()
{
	return MapSizeY_;
}

float Level2::GetMapSizeX()
{
	return MapSizeX_;
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

