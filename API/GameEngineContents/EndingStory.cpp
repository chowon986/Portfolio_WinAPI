#include "EndingStory.h"
#include "GameEngine/GameEngine.h"
#include <GameEngineBase/GameEngineInput.h>
#include "VideoPlayer.h"

EndingStory::EndingStory()
{
	DelayTime_ = 0.0f;
}

EndingStory::~EndingStory()
{
}

void EndingStory::Loading()
{
}

void EndingStory::DelayUpdate()
{
	if (true == EndingVideo_->IsVideoFinished() || true == GameEngineInput::GetInst()->IsDown("NextLevel"))
	{
		BgmPlayer.Stop();
		GameEngine::GetInst().ChangeLevel("Title");
	}
}

void EndingStory::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	BgmPlayer = GameEngineSound::SoundPlayControl("EndingStory.mp3");
	GameEngineLevelBase::LevelChangeStart(_PrevLevel);
	EndingVideo_ = CreateActor<VideoPlayer>();
	EndingVideo_->SetInfo("ending_frame_", 0, 1030, 60);
}
