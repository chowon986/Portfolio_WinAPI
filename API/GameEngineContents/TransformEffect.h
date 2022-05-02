#pragma once
#include <GameEngine/GameEngineActor.h>

enum class TransformEffectState
{
	TransformEffect,
	None
};

class GameEngineImage;
class TransformEffect : public GameEngineActor
{
public:
	TransformEffect();
	~TransformEffect();

	TransformEffect(const TransformEffect& _Other) = delete;
	TransformEffect(TransformEffect&& _Other) noexcept = delete;
	TransformEffect& operator=(const TransformEffect& _Other) = delete;
	TransformEffect& operator=(TransformEffect&& _Other) noexcept = delete;

public:
	void SetState(TransformEffectState _TransformEffectState);
	TransformEffectState GetState();
private:
	void StateUpdate();
	void UpdateTransformEffect();
	void UpdateNone();


protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	TransformEffectState TransformEffectState_;
	float4 StartPos_;
	GameEngineImage* ColMapImage_;
	GameEngineRenderer* Renderer_;
	GameEngineImage* Image_;
};