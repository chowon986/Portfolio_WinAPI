#include "Level1_4.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Background.h"
#include "Player.h"
#include "Monster.h"
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
	if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Cannon");
	}


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
	{
		Background* Stage1_4 = CreateActor<Background>((int)ORDER::BACKGROUND);
		Stage1_4->CreateRendererToScale("Stage1_4.bmp", float4(MapSizeX_, MapSizeY_), RenderPivot::CENTER, float4(1920.0f, 0.0f));
	}

	{
		Player_ = CreateActor<Player>((int)ORDER::PLAYER);
	}

	{
		Monster* Box = CreateActor<Monster>((int)ORDER::MONSTER);
		Box->CreateRenderer("Box.bmp", RenderPivot::CENTER, float4(890.0f, 350.0f));
	}


	{
		Monster* Fire = CreateActor<Monster>((int)ORDER::MONSTER);
		GameEngineRenderer* FireRenderer = Fire->CreateRenderer("monster0.bmp", RenderPivot::CENTER, float4(950.0f, 380.0f));
		GameEngineImage* FireImage = FireRenderer->GetImage();
		FireImage->CutCount(10, 26);
		FireRenderer->CreateAnimation("monster0.bmp", "FireIdel", 160, 164, 0.3f, true);
		FireRenderer->ChangeAnimation("FireIdel");
	}

	{
		Monster* Monster1 = CreateActor<Monster>((int)ORDER::MONSTER);
		GameEngineRenderer* Monster1Renderer = Monster1->CreateRenderer("monster0.bmp", RenderPivot::CENTER, float4(1500.0f, 380.0f));
		GameEngineImage* Monster1Image = Monster1Renderer->GetImage();
		Monster1Image->CutCount(10, 26);
		Monster1Renderer->CreateAnimation("monster0.bmp", "Monster1Idel", 216, 219, 0.3f, true);
		Monster1Renderer->ChangeAnimation("Monster1Idel");
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
		// 물에 빠지게 하기
		Monster* Waddledi = CreateActor<Monster>((int)ORDER::MONSTER);
		GameEngineRenderer* WaddlediRenderer = Waddledi->CreateRenderer("monster0.bmp", RenderPivot::CENTER, float4(2480.0f, 290.0f));
		GameEngineImage* WaddlediImage = WaddlediRenderer->GetImage();
		WaddlediImage->CutCount(10, 26);
		WaddlediRenderer->CreateAnimation("monster0.bmp", "WaddlediIdel", 7, 13, 0.3f, true);
		WaddlediRenderer->ChangeAnimation("WaddlediIdel");
	}

	{
		Monster* Monster1 = CreateActor<Monster>((int)ORDER::MONSTER);
		GameEngineRenderer* Monster1Renderer = Monster1->CreateRenderer("monster0.bmp", RenderPivot::CENTER, float4(2900.0f, 190.0f));
		GameEngineImage* Monster1Image = Monster1Renderer->GetImage();
		Monster1Image->CutCount(10, 26);
		Monster1Renderer->CreateAnimation("monster0.bmp", "Monster1Idel", 216, 219, 0.3f, true);
		Monster1Renderer->ChangeAnimation("Monster1Idel");
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
}