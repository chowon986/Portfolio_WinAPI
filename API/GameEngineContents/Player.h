#pragma once
#include <GameEngine/GameEngineActor.h>
#include "CharacterBase.h"

// Ό³Έν :
class Player : public CharacterBase
{
public:
	Player();
	~Player();

	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

protected:

private:
	float Speed_;

	void Start() override;
	void Render() override;
	void Update() override;

	virtual float GetSpeed() override;

	virtual bool CanWalk() override;
	virtual bool CanRun() override;
	virtual bool CanJump() override;
	bool CanMoveUp();
	bool CanMoveDown();

	virtual void Walk() override;
	virtual void Run() override;
	/*virtual void Attack() override;
	virtual void Die() override;*/
	virtual void Jump() override;
	void MoveUp();
	void MoveDown();
};

