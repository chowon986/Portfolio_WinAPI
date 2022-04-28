#pragma once
#include <GameEngine/GameEngineActor.h>

enum class DieEffectState
{
	DieEffect,
	CannonEffect,
	None
};

class DieEffect : public GameEngineActor
{
public:
	DieEffect();
	~DieEffect();

	DieEffect(const DieEffect& _Other) = delete;
	DieEffect(DieEffect&& _Other) noexcept = delete;
	DieEffect& operator=(const DieEffect& _Other) = delete;
	DieEffect& operator=(DieEffect&& _Other) noexcept = delete;

public:
	void SetState(DieEffectState _DieEffectState);
	DieEffectState GetState();
private:
	void StateUpdate();
	void UpdateDieEffect();
	void UpdateCannonEffect();
	void UpdateNone();


protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	DieEffectState DieEffectState_;
	float4 StartPos_;
	GameEngineImage* ColMapImage_;
	GameEngineRenderer* Renderer_;
	GameEngineImage* Image_;
};