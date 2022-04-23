#pragma once
#include <GameEngine/GameEngineActor.h>

enum class BeamAttackEffectState
{
	BeamRightAttackEffect,
	BeamLeftAttackEffect,
	None
};

class Player;
class BeamAttackEffect : public GameEngineActor
{
public:
	BeamAttackEffect();
	~BeamAttackEffect();

	BeamAttackEffect(const BeamAttackEffect& _Other) = delete;
	BeamAttackEffect(BeamAttackEffect&& _Other) noexcept = delete;
	BeamAttackEffect& operator=(const BeamAttackEffect& _Other) = delete;
	BeamAttackEffect& operator=(BeamAttackEffect&& _Other) noexcept = delete;

public:
	void SetState(BeamAttackEffectState _BeamAttackEffectState);
	BeamAttackEffectState GetState();
	void SetPlayer(Player* _Player) { Player_ = _Player; }

private:
	void StateUpdate();
	void UpdateBeamRightAttackEffect();
	void UpdateBeamLeftAttackEffect();
	void UpdateNone();


protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	BeamAttackEffectState BeamAttackEffectState_;
	float4 StartPos_;
	GameEngineImage* ColMapImage_;
	GameEngineCollision* CollisionOne_;
	GameEngineCollision* CollisionTwo_;
	GameEngineCollision* CollisionThree_;
	Player* Player_;

};