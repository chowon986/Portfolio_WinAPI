#pragma once
#include <GameEngine/GameEngineActor.h>

enum class SparkAttackEffectState
{
	SparkAttackEffect,
	None
};

class GameEngineImage;
class SparkAttackEffect : public GameEngineActor
{
public:
	SparkAttackEffect();
	~SparkAttackEffect();

	SparkAttackEffect(const SparkAttackEffect& _Other) = delete;
	SparkAttackEffect(SparkAttackEffect&& _Other) noexcept = delete;
	SparkAttackEffect& operator=(const SparkAttackEffect& _Other) = delete;
	SparkAttackEffect& operator=(SparkAttackEffect&& _Other) noexcept = delete;

public:
	void SetState(SparkAttackEffectState _SparkAttackEffectState);
	SparkAttackEffectState GetState();
private:
	void StateUpdate();
	void UpdateSparkAttackEffect();
	void UpdateNone();


protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	SparkAttackEffectState SparkAttackEffectState_;
	float4 StartPos_;
	GameEngineImage* ColMapImage_;
	GameEngineRenderer* Renderer_;
	GameEngineCollision* Collision_;
	GameEngineCollision* SparkEffectCollision_;
	GameEngineImage* Image_;
	float Time_;
};