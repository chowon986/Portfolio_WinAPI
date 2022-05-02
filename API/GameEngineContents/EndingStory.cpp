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

	if (true == EndingVideo_->IsVideoFinished())
	{
		GameEngine::GetInst().ChangeLevel("Title");
	}
}

void EndingStory::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	VideoPlayer* EndingVideo = CreateActor<VideoPlayer>();
	EndingVideo->SetInfo("ending_frame_", 0, 1030, 60);
}
