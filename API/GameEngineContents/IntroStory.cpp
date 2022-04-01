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
		if (true == GameEngineInput::GetInst()->IsPress("LevelChange"))
		{
			GameEngine::GlobalEngine().ChangeLevel("EndingStory");
		}
	}
}

void IntroStory::LevelChangeStart()
{
	IntroVideo_ = CreateActor<VideoPlayer>();
	IntroVideo_->SetInfo("intro_frame_", 438, 1200, 30);
}
