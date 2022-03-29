#pragma once
#include "Monster.h"

class SwordItem : public Monster
{
public:
	SwordItem();
	~SwordItem();

	SwordItem(const SwordItem& _Other) = delete;
	SwordItem(SwordItem&& _Other) noexcept = delete;
	SwordItem& operator=(const SwordItem& _Other) = delete;
	SwordItem& operator=(SwordItem&& _Other) noexcept = delete;

public:
	void Start();

protected:

private:

};