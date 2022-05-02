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
	if (0 >= GetCameraPos().x)
	{
		float4 CurCameraPos = GetCameraPos();
		CurCameraPos.x = 0;
		SetCameraPos(CurCameraPos);
	}

	if (0 >= GetCameraPos().y)
	{
		float4 CurCameraPos = GetCameraPos();
		CurCameraPos.y = 0;
		SetCameraPos(CurCameraPos);
	}

	float CameraRectX = 768;
	float CameraRectY = 576;

	if (GetMapSizeX() <= GetCameraPos().x + CameraRectX)
	{
		float4 CurCameraPos = GetCameraPos();
		CurCameraPos.x = static_cast<int>(GetCameraPos().ix() - (GetCameraPos().ix() + CameraRectX - GetMapSizeX()));
		SetCameraPos(CurCameraPos);
	}

	if (GetMapSizeY() <= GetCameraPos().y + CameraRectY)
	{
		float4 CurCameraPos = GetCameraPos();
		CurCameraPos.y = static_cast<int>(GetCameraPos().iy() - (GetCameraPos().iy() + CameraRectY - GetMapSizeY()));
		SetCameraPos(CurCameraPos);
	}
}

void IntroStory::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	IntroVideo_ = CreateActor<VideoPlayer>();
	IntroVideo_->SetInfo("intro_frame_", 438, 1200, 30);
	BgmPlayer = GameEngineSound::SoundPlayControl("IntroStory.mp3");
}
