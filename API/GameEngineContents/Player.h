#pragma once
#include <GameEngine/GameEngineActor.h>
#include "CharacterBase.h"

enum class KirbyClass
{
	PIG,
	SPARK,
	SWORD,
	FIRE,
	ICE,
	ANIMAL,
	BEAM,
};

enum class KirbyState
{
	IDLE,
	WALK,
	RUN,
	FLY,
	FLYSTAY,
	FLYATTACK,
	FLYEND,
	EATSTART,
	EAT,
	EATEND,
	STARATTACK,
	TRANSFORM,
	TRANSFORMEND,
	JUMP,
	JUMPING,
	UP,
	DOWN,
	SLIDE,
	SLIDESTAY,
	GETDAMAGE,
	DIE,
};

class GameEngineImage;
class GameEngineRenderer;
class GameEngineCollision;
class GameEngineLevel;
class Player : public CharacterBase
{
public:
	float4 PrevPos_;
	Player();
	~Player();

	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	inline void SetHPCount(int _HPCount) { HPCount_ = _HPCount; }
	inline int GetHPCount() { return HPCount_; }

protected:
	GameEngineCollision* KirbyCol_;

private:
	GameEngineRenderer* Renderer_;
	GameEngineRenderer* SparkKirbyRenderer_;

	GameEngineRenderer* AttackEffectRenderer_;
	GameEngineCollision* AttackEffectCol_;
	int HPCount_;

	float Gravity_;
	float AccGravity_;
	float JumpHeight_;
	float Time_;
	float Speed_;
	GameEngineImage* ColMapImage_;
	GameEngineLevel* Level_;
	Player* Player_;
	KirbyClass KirbyClass_;
	KirbyState KirbyState_;
	std::string Dir_;

	void SetState(KirbyState _PrevState);
	void SetSpeed(float _Speed) { Speed_ = _Speed; }
	KirbyState GetState();


	void SetKirbyClass(KirbyClass _KirbyClass);
	KirbyClass GetKirbyClass();

	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

	void CorrectPos();

	void CheckCollision();

	void UpdateAnimation();
	void StateUpdate();

	//virtual float GetSpeed() override;
	virtual bool CanWalk() override;
	virtual bool CanRun() override;
	virtual bool CanJump() override;

	bool CanFly();
	bool CanInhale();
	bool CanHover();
	bool CanEat();
	bool CanMoveUp();
	bool CanMoveDown();

	/*virtual void Attack() override;
	virtual void Die() override;*/
	virtual void Jump() override;
	bool CheckMapCollision();
	void Hover();
	void Eat();
	void Fly();
	void Inhale();



	void UpdateIdle();
	void UpdateWalk();
	void UpdateRun();
	void UpdateFly();
	void UpdateFlyStay();
	void UpdateFlyAttack();
	void UpdateAttack();
	void UpdateDie();
	void UpdateUp();
	void UpdateDown();
	void UpdateHover();
	void UpdateInhale();
	void UpdateEatStart();
	void UpdateEat();
	void UpdateJump();
	void UpdateSlide();
	void UpdateSlideStay();
};
