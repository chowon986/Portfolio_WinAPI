#include "IntroStory.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include "VideoPlayer.h"

IntroStory::IntroStory()
	:IntroVideo_(nullptr)
{
}

IntroStory::~IntroStory()
{
}


void IntroStory::Loading()
{

}

void IntroStory::Update()
{
	if (true == IntroVideo_->IsVideoFinished())
	{
		BgmPlayer.Stop();
		GameEngine::GetInst().ChangeLevel("Level1");
	}

}

void IntroStory::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	IntroVideo_ = CreateActor<VideoPlayer>();
	IntroVideo_->SetInfo("intro_frame_", 438, 1200, 43.0f);
	BgmPlayer = GameEngineSound::SoundPlayControl("Test1.mp3");
}
