#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Player : public GameEngineActor
{
public:
	int LifeCount_;
	int HP_;
	
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Render() override;
	void Update() override;
	void Walk();
	void Run();
	void GoUp();
	void GoDown();
	void GetNewAbility();
	void Swim();
	void Attack();
	void RideWarpStar();
	void Throwaway();
	void Sliding();
	void Sit();
	void Hovering();
	void Blotting();
	void UseDoor();
};

