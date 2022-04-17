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
	WALK, // possible : ATTACK, FLY, JUMP, EAT, ABANDON, SLIDE, TAKEDMG,  
	RUN,  // possible : ATTACK, FLY, JUMP, EAT, ABANDON, SLIDE, TKDMG,
	UP,	  // Animal 상태에서 땅 파고 올라가는 상태
	DOWN, // possible : SLIDE 
	SLIDE,  
	FLY, 
	FLYSTAY,
	FLYATTACK,
	FLYEND,
	EATSTART, // possible : ATTACK
	EAT,      // possible : ATTACK
	EATEND,   // possible : ATTACK
	ATTACK,	  
	ABANDON,  
	TRANSFORM, 
	JUMPUP, // Possible : FLY
	JUMPING, // Possible : FLY
	JUMPDOWN, // Possible : FLY
	TAKEDAMAGE, // possible : ATTACK, FLY, JUMP, EAT, ABANDON, SLIDE,
	DIE,
};

class GameEngineImage;
class GameEngineRenderer;
class GameEngineCollision;
class GameEngineLevel;
class BotUI;
class Monster;
class StarAttackEffect;
enum class MonsterClass;
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
	GameEngineImage* PigImage_;

	StarAttackEffect* StarAttackEffect_;

	Monster* Monster_;
	MonsterClass MonClass_;

	int HPCount_;

	float Gravity_;
	float JumpHeight_;
	float Time_;
	float Speed_;
	GameEngineImage* ColMapImage_;
	GameEngineLevel* Level_;
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
	void UpdateFlyEnd();
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
	void UpdateTransform();
	void UpdateTransformEnd();

	//void UpdateEffect();
public:
	void SetStarAttackEffect(StarAttackEffect* _StarAttackEffect)
	{
		StarAttackEffect_ = _StarAttackEffect;
	}
};
