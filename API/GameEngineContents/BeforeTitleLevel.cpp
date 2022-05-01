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
}

BeforeTitleLevel::~BeforeTitleLevel()
{
}


void BeforeTitleLevel::Loading()
{

}


void BeforeTitleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	BeforeTitleVideo_ = CreateActor<VideoPlayer>();
	BeforeTitleVideo_->SetInfo("intro_frame_", 0, 400, 30.0f);

	BgmPlayer = GameEngineSound::SoundPlayControl("BeforeTitle.mp3");
}


void BeforeTitleLevel::Update()
{
	if (true == BeforeTitleVideo_->IsVideoFinished())
	{
		BgmPlayer.Stop();
		GameEngine::GetInst().ChangeLevel("Title");
	}
}