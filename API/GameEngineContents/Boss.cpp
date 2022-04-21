#include "Boss.h"
#include "Dedede.h"
#include "Player.h"
#include "Background.h"
#include "ContentsEnum.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>

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
	//BossLevelStartRenderer_->ChangeAnimation("End"); // dedede hp∞° 0¿Ã∏È

}

void Boss::LevelChangeStart()
{
	SetColMapImage("BossColMap.bmp");
	ColMapImage_ = GetColMapImage();

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
		// Player
		// need to chk : kirby pos
		Player_ = CreateActor<Player>((int)ORDER::PLAYER);
		Player_->SetPosition(float4(500.0f, 400.0f));
	}

	{
		// Boss
		Dedede* Dedede_ = CreateActor<Dedede>((int)ORDER::MONSTER);
		Dedede_->SetPosition(float4(640.0f, 440.0f));
	}

}
