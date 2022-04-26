#pragma once
#include <list>
#include <map>
#include <vector>
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>

class GameEngineActor;
struct ChangeOrderItem
{
	GameEngineActor* TargetObject; // �̳༮��
	int ChangeOrder; // �̷��� �ٲ��.
};

class GameEngine;
class GameEngineActor;
class GameEngineCollision;
class GameEngineRenderer; 
class GameEngineImage;
class GameEngineLevel : public GameEngineNameObject
{
	friend GameEngine;
	friend GameEngineActor;
	friend GameEngineCollision;
	friend GameEngineRenderer;

public:
	// constrcuter destructer
	GameEngineLevel();

	// �Ҹ��� virtual �߿�
	virtual ~GameEngineLevel();

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;


	template<typename ActorType>
	ActorType* CreateActor(int _Order = 0, const std::string& _Name = "")
	{
		ActorType* NewActor = new ActorType();
		GameEngineActor* StartActor = NewActor;
		NewActor->GameEngineUpdateObject::SetOrder(_Order);
		NewActor->SetName(_Name);
		NewActor->SetLevel(this);
		StartActor->Start();
		std::list<GameEngineActor*>& Group = AllActor_[_Order];
		Group.push_back(NewActor);

		//// _Order ���͵��� ���ư��� ������ �ǹ��ϰ� �ȴ�.
		//// insert�� find�� ���ÿ�
		//std::map<int, std::list<GameEngineActor*>>::iterator FindGroup
		//	= AllActor_.find(_Order);

		//if (FindGroup == AllActor_.end())
		//{

		//	// AllActor_.insert(std::make_pair(_Order, std::list<GameEngineActor*>()));
		//	// �̰Դ� ����
		//	AllActor_.insert(
		//		std::map<int, std::list<GameEngineActor*>>::value_type(_Order, std::list<GameEngineActor*>())
		//	);
		//	FindGroup = AllActor_.find(_Order);
		//}

		return NewActor;
	}

	inline float4 GetCameraPos() 
	{
		return CameraPos_;
	}

	inline void MoveCameraPos(const float4& _Value)
	{
		CameraPos_ += _Value;
	}

	inline void SetCameraPos(const float4& _Value )
	{
		CameraPos_  = _Value;
	}

	virtual float GetMapSizeX() { return MapSizeX_; }
	virtual float GetMapSizeY() { return MapSizeY_; }
	virtual void SetMapSizeX(float _MapSizeX) { MapSizeX_ = _MapSizeX; }
	virtual void SetMapSizeY(float _MapSizeY) { MapSizeY_ = _MapSizeY; }

private:
	float MapSizeX_;
	float MapSizeY_;

public:
	void SetColMapImage(std::string _name);
	virtual GameEngineImage* GetColMapImage();

protected:
	GameEngineImage* ColMapImage_;
protected:
	// �����Լ�
	// ��������鼭 ���ҽ��� ���͸� ���鶧 ���
	virtual void Loading() = 0;
	// �� ������ ���� �����϶� �ؾ������� �����Ѵ�.
	virtual void Update() = 0;
	// Current���� => Next������ �����Ҷ� ���緹���� �����ϴ� �Լ�.
	virtual void LevelChangeStart() {}
	// Current���� => Next������ �����Ҷ� ���������� �����ϴ� �Լ�.
	virtual void LevelChangeEnd() {}

private:
	// std::vector�� �����ϴ°� �� ���ٰ� ����..
	std::map<int, std::list<GameEngineActor*>> AllActor_;

	std::vector<ChangeOrderItem> ChangeOrderList;

	float4 CameraPos_;


	void ActorUpdate();
	void ActorRender();
	void CollisionDebugRender();
	void ActorRelease();

private:
	std::map<int, std::list<GameEngineRenderer*>> AllRenderer_;

	void AddRenderer(GameEngineRenderer* _Renderer);

	void ChangeUpdateOrder(GameEngineActor* _Actor, int _Oreder);

	void ChangeRenderOrder(GameEngineRenderer* _Renderer, int _NewOrder);


private:
	// ������ ���Ͱ� ������ ���� ����� Level�� �Ժη� GameEngineCollision*�� delete �ϴ� ���� ������ �ȵȴ�.,
	std::map<std::string, std::list<GameEngineCollision*>> AllCollision_;

	void AddCollision(const std::string& _GroupName, GameEngineCollision* _Collision);
};
