#include "Level1_4.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Background.h"
#include "Player.h"
#include "Monster1.h"
#include "Fire.h"
#include "Waddledee.h"
#include "ContentsEnum.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImage.h>
#include "Tomato.h"
#include "Box.h"
#include "BombBox.h"
#include "Bomb.h"
#include "BotUI.h"
#include "StarAttackEffect.h"
#include "IceAttackEffect.h"
#include "AttackEffect.h"
#include "SparkAttackEffect.h"
#include "FireAttackEffect.h"
#include "RunEffect.h"

Level1_4::Level1_4()
	: Player_(nullptr)
	, PlayerStatus_(nullptr)
	, Cannon_(nullptr)
{
}

Level1_4::~Level1_4()
{
}


void Level1_4::Loading()
{
}

void Level1_4::Update()
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

void Level1_4::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{

}

void Level1_4::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	SetMapSizeX(4608);
	SetMapSizeY(576);
	SetColMapImage("Stage1_4ColMap.bmp");
	ColMapImage_ = GetColMapImage();

	if (ColMapImage_ == nullptr)
	{
		MsgBoxAssert("충돌맵 이미지를 찾지 못했습니다.")
	}

	{
		Background* Stage1_4 = CreateActor<Background>((int)ORDER::BACKGROUND);
		Stage1_4->CreateRendererToScale("Stage1_4.bmp", float4(GetMapSizeX(), GetMapSizeY()), static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(1920.0f, 0.0f));
	}

	{
		Player_ = CreateActor<Player>((int)ORDER::PLAYER);
		Player_->SetPosition(float4(205.0f, 430.0f));
		Player_->SetMapStartPos(float4(205.0f, 430.0f));
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
		Box* Box_ = CreateActor<Box>((int)ORDER::OBSTRUCTION);
		Box_->SetPosition(float4(890.0f, 350.0f));
	}

	{
		Fire* Fire_ = CreateActor<Fire>((int)ORDER::MONSTER);
		Fire_->SetPosition(float4(950.0f, 380.0f));
	}

	{
		Monster1* Monster1_ = CreateActor<Monster1>((int)ORDER::MONSTER);
		Monster1_->SetPosition(float4(1500.0f, 380.0f));
	}

	{
		Tomato* Tomato_ = CreateActor<Tomato>((int)ORDER::ITEM);
		Tomato_->SetPosition(float4(2140.0f, 100.0f));
	}

	{
		Background* Wave = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* WaveRenderer = Wave->CreateRenderer("Wave.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(1751.0f, 80.0f));
		GameEngineImage* WaveImage = WaveRenderer->GetImage();
		WaveImage->CutCount(2, 2);
		WaveRenderer->CreateAnimation("Wave.bmp", "Wave", 0, 3, 0.5f, true);
		WaveRenderer->ChangeAnimation("Wave");
	}

	{
		Monster1* Monster1_ = CreateActor<Monster1>((int)ORDER::MONSTER);
		Monster1_->SetPosition(float4(3300.0f, 480.0f));
	}

	{
		Bomb* Bomb_ = CreateActor<Bomb>((int)ORDER::OBSTRUCTION);
		Bomb_->SetPosition(float4(3920.0f, 210.0f));
	}

	{
		BombBox* BombBox1 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
		BombBox1->SetPosition(float4(3965.0f, 210.0f));
		BombBox* BombBox2 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
		BombBox2->SetPosition(float4(4010.0f, 210.0f));
		BombBox* BombBox3 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
		BombBox3->SetPosition(float4(4055.0f, 210.0f));
		BombBox* BombBox4 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
		BombBox4->SetPosition(float4(4100.0f, 210.0f));
		BombBox* BombBox5 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
		BombBox5->SetPosition(float4(4145.0f, 210.0f));
		BombBox* BombBox6 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
		BombBox6->SetPosition(float4(3965.0f, 165.0f));
		BombBox* BombBox7 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
		BombBox7->SetPosition(float4(4010.0f, 165.0f));
		BombBox* BombBox8 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
		BombBox8->SetPosition(float4(4055.0f, 165.0f));
		BombBox* BombBox9 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
		BombBox9->SetPosition(float4(4100.0f, 165.0f));
		BombBox* BombBox10 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
		BombBox10->SetPosition(float4(4145.0f, 165.0f));
		BombBox* BombBox11 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
		BombBox11->SetPosition(float4(3965.0f, 120.0f));
		BombBox* BombBox12 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
		BombBox12->SetPosition(float4(4010.0f, 120.0f));
		BombBox* BombBox13 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
		BombBox13->SetPosition(float4(4055.0f, 120.0f));
		BombBox* BombBox14 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
		BombBox14->SetPosition(float4(4100.0f, 120.0f));
		BombBox* BombBox15 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
		BombBox15->SetPosition(float4(4145.0f, 120.0f));
		BombBox* BombBox16 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
		BombBox16->SetPosition(float4(3965.0f, 75.0f));
		BombBox* BombBox17 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
		BombBox17->SetPosition(float4(4010.0f, 75.0f));
		BombBox* BombBox18 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
		BombBox18->SetPosition(float4(4055.0f, 75.0f));
		BombBox* BombBox19 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
		BombBox19->SetPosition(float4(4100.0f, 75.0f));
		BombBox* BombBox20 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
		BombBox20->SetPosition(float4(4145.0f, 75.0f));
		BombBox* BombBox21 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
		BombBox21->SetPosition(float4(3965.0f, 30.0f));
		BombBox* BombBox22 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
		BombBox22->SetPosition(float4(4010.0f, 30.0f));
		BombBox* BombBox23 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
		BombBox23->SetPosition(float4(4055.0f, 30.0f));
		BombBox* BombBox24 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
		BombBox24->SetPosition(float4(4100.0f, 30.0f));
		BombBox* BombBox25 = CreateActor<BombBox>((int)ORDER::OBSTRUCTION);
		BombBox25->SetPosition(float4(4145.0f, 30.0f));
	}

	Background* Door = CreateActor<Background>((int)ORDER::BACKGROUND);
	GameEngineRenderer* DoorRenderer = Door->CreateRenderer("BigDoor.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(4120.0f, -117.0f));
	Cannon_ = Door->CreateCollision("Cannon", float4(90.0f, 70.0f), float4(4120.0f, -87.0f));

	Background* DoorStar = CreateActor<Background>((int)ORDER::BACKGROUND);
	GameEngineRenderer* DoorStarRenderer = DoorStar->CreateRenderer("BigDoorStar.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, float4(4120.0f, -140.0f));
	GameEngineImage* DoorStarImage = DoorStarRenderer->GetImage();
	DoorStarImage->CutCount(6, 2);
	DoorStarRenderer->CreateAnimation("BigDoorStar.bmp", "BigDoorStar", 0, 11, 0.05f, true);
	DoorStarRenderer->ChangeAnimation("BigDoorStar");
}
