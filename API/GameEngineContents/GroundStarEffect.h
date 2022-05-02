#pragma once
#include <GameEngine/GameEngineActor.h>

enum class GroundStarEffectState
{
	GroundStarEffect,
	None,
};

class GroundStarEffect : public GameEngineActor
{
public:
	GroundStarEffect();
	~GroundStarEffect();

	GroundStarEffect(const GroundStarEffect& _Other) = delete;
	GroundStarEffect(GroundStarEffect&& _Other) noexcept = delete;
	GroundStarEffect& operator=(const GroundStarEffect& _Other) = delete;
	GroundStarEffect& operator=(GroundStarEffect&& _Other) noexcept = delete;

public:
	void SetState(GroundStarEffectState _GroundStarEffectState);
	GroundStarEffectState GetState();
private:
	void StateUpdate();
	void UpdateGroundStarEffect();
	void UpdateNone();


protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	GroundStarEffectState GroundStarEffectState_;
	GameEngineImage* ColMapImage_;
	GameEngineRenderer* Renderer_;
	GameEngineCollision* Collision_;
	GameEngineImage* Image_;
};