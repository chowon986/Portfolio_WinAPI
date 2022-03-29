#pragma once
#include "Monster.h"

class BigTresureChest : public Monster
{
public:
	BigTresureChest();
	~BigTresureChest();

	BigTresureChest(const BigTresureChest& _Other) = delete;
	BigTresureChest(BigTresureChest&& _Other) noexcept = delete;
	BigTresureChest& operator=(const BigTresureChest& _Other) = delete;
	BigTresureChest& operator=(BigTresureChest&& _Other) noexcept = delete;

protected:
	void Start();

private:

};
