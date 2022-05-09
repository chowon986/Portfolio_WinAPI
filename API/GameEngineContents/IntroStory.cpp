#include "IntroStory.h"
#include "GameEngineBase/GameEngineInput.h"
#include "GameEngine/GameEngine.h"
#include "VideoPlayer.h"

IntroStory::IntroStory()
	:IntroVideo_(nullptr)
{
	DelayTime_ = 0.0f;
}

IntroStory::~IntroStory()
{
}


void IntroStory::Loading()
{

}

void IntroStory::DelayUpdate()
{
	if (true == IntroVideo_->IsVideoFinished() || true == GameEngineInput::GetInst()->IsDown("NextLevel"))
	{
		BgmPlayer.Stop();
		GameEngine::GetInst().ChangeLevel("Level1");
	}

}

void IntroStory::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	GameEngineLevelBase::LevelChangeStart(_PrevLevel);
	IntroVideo_ = CreateActor<VideoPlayer>();
	IntroVideo_->SetInfo("intro_frame_", 438, 1200, 43.0f);
	BgmPlayer = GameEngineSound::SoundPlayControl("Test1.mp3");
}
