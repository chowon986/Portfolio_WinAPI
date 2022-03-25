#pragma once
#include <GameEngineBase/GameEngineMath.h>

// Ό³Έν :
class bullet
{
public:
	int HP_;
	float4 Pos_;

public:
	bullet();
	~bullet();

	bullet(const bullet& _Other) = delete;
	bullet(bullet&& _Other) noexcept = delete;
	bullet& operator=(const bullet& _Other) = delete;
	bullet& operator=(bullet&& _Other) noexcept = delete;

protected:

private:
	void Walk();
	void Jump();
	bool IsDie();
	void attack();
	void GetPos(float4 _Pos);
};

