#pragma once
#include "Monster.h"

class BigBox : public Monster
{
public:
	BigBox();
	~BigBox();

	BigBox(const BigBox& _Other) = delete;
	BigBox(BigBox&& _Other) noexcept = delete;
	BigBox& operator=(const BigBox& _Other) = delete;
	BigBox& operator=(BigBox&& _Other) noexcept = delete;

protected:
	void Start();

private:

};
