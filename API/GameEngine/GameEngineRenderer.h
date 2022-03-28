#pragma once
#include "GameEngineActorSubObject.h"
#include "GameEngineEnum.h"
class GameEngineImage;
class GameEngineRenderer : public GameEngineActorSubObject
{
	friend GameEngineActor;

public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	inline void SetTransColor(unsigned int _Color)
	{
		TransColor_ = _Color;
	}

	inline void SetPivot(const float4& _Pos) // �� �ϳ��� ������
	{
		RenderPivot_ = _Pos;
	}

	inline void SetType(const RenderPivot& _Type) // bot, center �� ����
	
	{
		PivotType_ = _Type;
	}

	inline void SetScaleMode(const RenderScaleMode& _Mode)
	{
		ScaleMode_ = _Mode;
	}

	void SetImageScale(); // image

	inline void SetScale(const float4& _Scale) // �̹��� ũ�� �״�� �� �����µ� �� scale�� �־��ִ°�? ũ�⸦ �����Ϸ��� pivottype:user
	{
		ScaleMode_ = RenderScaleMode::User;
		RenderScale_ = _Scale;
	}

	


	void SetImage(const std::string& _Name);

	// Scale�� �ƹ��͵� ���� ������ -1�� �����ϱ� ���ؼ�
	void SetIndex(size_t _Index, float4 _Scale = {-1.0f, -1.0f});

protected:
	void Render();

private:
	GameEngineImage* Image_;
	RenderPivot PivotType_; // ����, bot
	RenderScaleMode ScaleMode_;


	float4 RenderPivot_;
	// ȭ�鿡 �׷����� ũ��
	float4 RenderScale_;

	// �̹������� �߶󳻴� ũ��
	float4 RenderImageScale_;
	float4 RenderImagePivot_;

	unsigned int TransColor_;

};

