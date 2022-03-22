#pragma once
#include "GameEngineEnum.h"
#include "GameEngineActorSubObject.h"

class GameEngineImage;
class GameEngineRenderer : public GameEngineActorSubObject

{
	friend GameEngineActor;

public:
	// constrcuter destructer
	GameEngineRenderer();
	virtual ~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	inline void SetPivot(const float4& _Pos)
	{
		RenderPivot_ = _Pos;
	}

	inline void SetType(const RenderPivot& _Type)
	{
		PivotType = _Type;
	}

	void SetImage(const std::string& _Name);

protected:
	void Render();

private:
	GameEngineImage* Image_;
	RenderPivot PivotType; // ºæ≈Õ, bot
	float4 RenderPivot_;
};

