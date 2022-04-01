#include "EndingStory.h"
#include "GameEngine/GameEngine.h"
#include <GameEngineBase/GameEngineInput.h>
#include "VideoPlayer.h"

EndingStory::EndingStory()
{
}

EndingStory::~EndingStory()
{
}

void EndingStory::Loading()
{
}

void EndingStory::Update()
{
}

void EndingStory::LevelChangeStart()
{
	VideoPlayer* EndingVideo = CreateActor<VideoPlayer>();
	EndingVideo->SetInfo("ending_frame_", 0, 1030, 60);
}
