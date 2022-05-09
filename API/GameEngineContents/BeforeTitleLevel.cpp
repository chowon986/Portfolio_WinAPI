#include "BeforeTitleLevel.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include "Background.h"
#include "VideoPlayer.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>


BeforeTitleLevel::BeforeTitleLevel()
	:BeforeTitleVideo_(nullptr)
{
	DelayTime_ = 0.0f;
}

BeforeTitleLevel::~BeforeTitleLevel()
{
}


void BeforeTitleLevel::Loading()
{

}


void BeforeTitleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	GameEngineLevelBase::LevelChangeStart(_PrevLevel);

	BeforeTitleVideo_ = CreateActor<VideoPlayer>();
	BeforeTitleVideo_->SetInfo("intro_frame_", 0, 430, 28.5f);

	BgmPlayer = GameEngineSound::SoundPlayControl("BeforeTitle.mp3");
}

void BeforeTitleLevel::DelayUpdate()
{
	if (true == BeforeTitleVideo_->IsVideoFinished() || true == GameEngineInput::GetInst()->IsDown("NextLevel"))
	{
		BgmPlayer.Stop();
		GameEngine::GetInst().ChangeLevel("Title");
	}
}