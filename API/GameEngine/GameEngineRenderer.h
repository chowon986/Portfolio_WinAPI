#pragma once
#include "GameEngineActorSubObject.h"
#include "GameEngineEnum.h"

class GameEngineImage;
class GameEngineRenderer : public GameEngineActorSubObject
{
	friend GameEngineActor;

public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	inline void SetTransColor(unsigned int _Color)
	{
		TransColor_ = _Color;
	}

	inline void SetPivot(const float4& _Pos)		// 점 하나를 잡은거
	{
		RenderPivot_ = _Pos;
	}

	inline void SetType(const RenderPivot& _Type) 		// bot, center 중 선택
	{
		PivotType_ = _Type;
	}

	inline void SetScaleMode(const RenderScaleMode& _Mode)
	{
		ScaleMode_ = _Mode;
	}

	void SetImageScale(); // image

	inline void SetScale(const float4& _Scale) // 이미지 크기 그대로 잘 나오는데 왜 scale을 넣어주는가? 크기를 조절하려고 pivottype:user
	{
		ScaleMode_ = RenderScaleMode::User;
		RenderScale_ = _Scale;
	}

	


	void SetImage(const std::string& _Name);

	void SetIndex(size_t _Index);

protected:
	void Render();

private:
	GameEngineImage* Image_;
	RenderPivot PivotType_; // 센터, bot
	RenderScaleMode ScaleMode_;


	float4 RenderPivot_;


	// 
	float4 RenderScale_;

	float4 RenderImageScale_;
	float4 RenderImagePivot_;

	unsigned int TransColor_;

};

