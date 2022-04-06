#include "Level1_4.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Background.h"
#include "Player.h"
#include "Monster1.h"
#include "Fire.h"
#include "Waddledi.h"
#include "ContentsEnum.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImage.h>

Level1_4::Level1_4()
	: Player_(nullptr)
	, MapSizeX_(4608)
	, MapSizeY_(576)
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
	//if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	//{
	//	GameEngine::GlobalEngine().ChangeLevel("Cannon");
	//}


	// CHK : CAMERA SETTING
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

void Level1_4::LevelChangeStart()
{
	SetColMapImage("Stage1_4ColMap.bmp");
	ColMapImage_ = GetColMapImage();

	if (ColMapImage_ == nullptr)
	{
		MsgBoxAssert("충돌맵 이미지를 찾지 못했습니다.")
	}

	{
		Background* Stage1_4 = CreateActor<Background>((int)ORDER::BACKGROUND);
		Stage1_4->CreateRendererToScale("Stage1_4.bmp", float4(MapSizeX_, MapSizeY_), RenderPivot::CENTER, float4(1920.0f, 0.0f));
	}

	{
		Player_ = CreateActor<Player>((int)ORDER::PLAYER);
		Player_->SetPosition(float4(205.0f, 430.0f));
	}

	{
		Monster* Box = CreateActor<Monster>((int)ORDER::MONSTER);
		Box->CreateRenderer("Box.bmp", RenderPivot::CENTER, float4(890.0f, 350.0f));
	}

	{
		Fire* Fire_ = CreateActor<Fire>((int)ORDER::MONSTER);
		Fire_->SetPosition(float4(950.0f, 380.0f));
		GameEngineCollision* FireCol = Fire_->CreateCollision("BasicMonster", float4(50.0f, 50.0f), float4(0.0f, -30.0f));
	}

	{
		Monster1* Monster1_ = CreateActor<Monster1>((int)ORDER::MONSTER);
		Monster1_->SetPosition(float4(1500.0f, 380.0f));
		GameEngineCollision* Monster1Col = Monster1_->CreateCollision("BasicMonster", float4(50.0f, 50.0f), float4(0.0f, -30.0f));
	}

	{
		Monster* Tomato = CreateActor<Monster>((int)ORDER::MONSTER);
		Tomato->CreateRenderer("Tomato.bmp", RenderPivot::CENTER, float4(2140.0f, 100));
	}

	{
		Background* Wave = CreateActor<Background>((int)ORDER::BACKGROUND);
		GameEngineRenderer* WaveRenderer = Wave->CreateRenderer("Wave.bmp", RenderPivot::CENTER, float4(1751.0f, 80.0f));
		GameEngineImage* WaveImage = WaveRenderer->GetImage();
		WaveImage->CutCount(2, 2);
		WaveRenderer->CreateAnimation("Wave.bmp", "Wave", 0, 3, 0.5f, true);
		WaveRenderer->ChangeAnimation("Wave");
	}

	{
		// 물에 빠지게 하기 (왼쪽 이동)
		Waddledi* Waddledi_ = CreateActor<Waddledi>((int)ORDER::MONSTER);
		Waddledi_->SetPosition(float4(2480.0f, 290.0f));
		GameEngineCollision* WaddlediCol = Waddledi_->CreateCollision("BasicMonster", float4(50.0f, 50.0f), float4(0.0f, -30.0f));
	}

	{
		Monster1* Monster1_ = CreateActor<Monster1>((int)ORDER::MONSTER);
		Monster1_->SetPosition(float4(2900.0f, 190.0f));
		GameEngineCollision* Monster1Col = Monster1_->CreateCollision("BasicMonster", float4(50.0f, 50.0f), float4(0.0f, -30.0f));
	}

	{
		Monster* Bomb = CreateActor<Monster>((int)ORDER::MONSTER);
		Bomb->CreateRenderer("Bomb.bmp", RenderPivot::CENTER, float4(3920.0f, 210.0f));
	}

	{
		Monster* BombBox1 = CreateActor<Monster>((int)ORDER::MONSTER);
		BombBox1->CreateRenderer("BombBox.bmp", RenderPivot::CENTER, float4(3965.0f, 210.0f));
		Monster* BombBox2 = CreateActor<Monster>((int)ORDER::MONSTER);
		BombBox2->CreateRenderer("BombBox.bmp", RenderPivot::CENTER, float4(4010.0f, 210.0f));
		Monster* BombBox3 = CreateActor<Monster>((int)ORDER::MONSTER);
		BombBox3->CreateRenderer("BombBox.bmp", RenderPivot::CENTER, float4(4055.0f, 210.0f));
		Monster* BombBox4 = CreateActor<Monster>((int)ORDER::MONSTER);
		BombBox4->CreateRenderer("BombBox.bmp", RenderPivot::CENTER, float4(4100.0f, 210.0f));
		Monster* BombBox5 = CreateActor<Monster>((int)ORDER::MONSTER);
		BombBox5->CreateRenderer("BombBox.bmp", RenderPivot::CENTER, float4(4145.0f, 210.0f));
		Monster* BombBox6 = CreateActor<Monster>((int)ORDER::MONSTER);
		BombBox6->CreateRenderer("BombBox.bmp", RenderPivot::CENTER, float4(3965.0f, 165.0f));
		Monster* BombBox7 = CreateActor<Monster>((int)ORDER::MONSTER);
		BombBox7->CreateRenderer("BombBox.bmp", RenderPivot::CENTER, float4(4010.0f, 165.0f));
		Monster* BombBox8 = CreateActor<Monster>((int)ORDER::MONSTER);
		BombBox8->CreateRenderer("BombBox.bmp", RenderPivot::CENTER, float4(4055.0f, 165.0f));
		Monster* BombBox9 = CreateActor<Monster>((int)ORDER::MONSTER);				 
		BombBox9->CreateRenderer("BombBox.bmp", RenderPivot::CENTER, float4(4100.0f, 165.0f));
		Monster* BombBox10 = CreateActor<Monster>((int)ORDER::MONSTER);				 
		BombBox10->CreateRenderer("BombBox.bmp", RenderPivot::CENTER, float4(4145.0f, 165.0f));
		Monster* BombBox11 = CreateActor<Monster>((int)ORDER::MONSTER);
		BombBox11->CreateRenderer("BombBox.bmp", RenderPivot::CENTER, float4(3965.0f, 120.0f));
		Monster* BombBox12 = CreateActor<Monster>((int)ORDER::MONSTER);
		BombBox12->CreateRenderer("BombBox.bmp", RenderPivot::CENTER, float4(4010.0f, 120.0f));
		Monster* BombBox13 = CreateActor<Monster>((int)ORDER::MONSTER);
		BombBox13->CreateRenderer("BombBox.bmp", RenderPivot::CENTER, float4(4055.0f, 120.0f));
		Monster* BombBox14 = CreateActor<Monster>((int)ORDER::MONSTER);
		BombBox14->CreateRenderer("BombBox.bmp", RenderPivot::CENTER, float4(4100.0f, 120.0f));
		Monster* BombBox15 = CreateActor<Monster>((int)ORDER::MONSTER);
		BombBox15->CreateRenderer("BombBox.bmp", RenderPivot::CENTER, float4(4145.0f, 120.0f));
		Monster* BombBox16 = CreateActor<Monster>((int)ORDER::MONSTER);
		BombBox16->CreateRenderer("BombBox.bmp", RenderPivot::CENTER, float4(3965.0f, 75.0f));
		Monster* BombBox17 = CreateActor<Monster>((int)ORDER::MONSTER);
		BombBox17->CreateRenderer("BombBox.bmp", RenderPivot::CENTER, float4(4010.0f, 75.0f));
		Monster* BombBox18 = CreateActor<Monster>((int)ORDER::MONSTER);
		BombBox18->CreateRenderer("BombBox.bmp", RenderPivot::CENTER, float4(4055.0f, 75.0f));
		Monster* BombBox19 = CreateActor<Monster>((int)ORDER::MONSTER);
		BombBox19->CreateRenderer("BombBox.bmp", RenderPivot::CENTER, float4(4100.0f, 75.0f));
		Monster* BombBox20 = CreateActor<Monster>((int)ORDER::MONSTER);
		BombBox20->CreateRenderer("BombBox.bmp", RenderPivot::CENTER, float4(4145.0f, 75.0f));
		Monster* BombBox21 = CreateActor<Monster>((int)ORDER::MONSTER);
		BombBox21->CreateRenderer("BombBox.bmp", RenderPivot::CENTER, float4(3965.0f, 30.0f));
		Monster* BombBox22 = CreateActor<Monster>((int)ORDER::MONSTER);
		BombBox22->CreateRenderer("BombBox.bmp", RenderPivot::CENTER, float4(4010.0f, 30.0f));
		Monster* BombBox23 = CreateActor<Monster>((int)ORDER::MONSTER);
		BombBox23->CreateRenderer("BombBox.bmp", RenderPivot::CENTER, float4(4055.0f, 30.0f));
		Monster* BombBox24 = CreateActor<Monster>((int)ORDER::MONSTER);
		BombBox24->CreateRenderer("BombBox.bmp", RenderPivot::CENTER, float4(4100.0f, 30.0f));
		Monster* BombBox25 = CreateActor<Monster>((int)ORDER::MONSTER);
		BombBox25->CreateRenderer("BombBox.bmp", RenderPivot::CENTER, float4(4145.0f, 30.0f));
	}

	Background* Door = CreateActor<Background>((int)ORDER::BACKGROUND);
	Cannon_ = Door->CreateCollision("Cannon", float4(90.0f, 70.0f), float4(4120.0f, -87.0f));
}

float Level1_4::GetMapSizeX()
{
	return MapSizeX_;
}

float Level1_4::GetMapSizeY()
{
	return MapSizeY_;
}