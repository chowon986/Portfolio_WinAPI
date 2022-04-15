#pragma once
#include <GameEngine/GameEngineActor.h>
#include "CharacterBase.h"

enum class KirbyClass
{
	DEFAULT,
	PIG,
	SPARK,
	SWORD,
	FIRE,
	ICE,
	ANIMAL,
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
	JUMPUP,
	JUMPING,
	JUMPDOWN,
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
class BotUI;
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

	void SetKirbyClass(KirbyClass _KirbyClass);
	KirbyClass GetKirbyClass();
protected:

private:
	GameEngineRenderer* Renderer_; // Default
	GameEngineRenderer* SparkKirbyRenderer_;
	GameEngineRenderer* PigRenderer_;
	GameEngineRenderer* SwordRenderer_;
	GameEngineRenderer* FireRenderer_;
	GameEngineRenderer* IceRenderer_;
	GameEngineRenderer* AnimalRenderer_;


	GameEngineRenderer* AttackEffectRenderer_;

	GameEngineCollision* KirbyCol_;
	GameEngineCollision* EatCol_;


	GameEngineImage* Image_;
	GameEngineImage* SwordKirbyImage_;
	GameEngineImage* IceKirbyImage_;


	std::string MonName_;

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
	KirbyState GetState() { return KirbyState_; }


	void ClassUpdate();

	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;

	void CorrectPos();

	void CheckCollision();
	void StateUpdate();
	bool CheckMapCollision();


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
	void UpdateEatEnd();
	void UpdateJumpUp();
	void UpdateJumping();
	void UpdateJumpDown();
	void UpdateSlide();
	void UpdateSlideStay();
	void UpdateTransform();
	void UpdateTransformEnd();
	void UpdateEffect();
};
