#pragma once
#include "Monster.h"

class FireItem : public Monster
{
public:
	FireItem();
	~FireItem();

	FireItem(const FireItem& _Other) = delete;
	FireItem(FireItem&& _Other) noexcept = delete;
	FireItem& operator=(const FireItem& _Other) = delete;
	FireItem& operator=(FireItem&& _Other) noexcept = delete;

public:
	void Start();

protected:

private:

};