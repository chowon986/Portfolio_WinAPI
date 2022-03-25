#pragma once

class GameEngineMath
{
private:
	GameEngineMath();
	~GameEngineMath();

	GameEngineMath(const GameEngineMath& _Other) = delete;
	GameEngineMath(GameEngineMath&& _Other) noexcept = delete;
	GameEngineMath& operator=(const GameEngineMath& _Other) = delete;
	GameEngineMath& operator=(GameEngineMath&& _Other) noexcept = delete;

protected:

private:

};

class float4
{
public:
	static float4 LEFT;
	static float4 RIGHT;
	static float4 UP;
	static float4 DOWN;

	float x;
	float y;
	float z;
	float w;

public:
	bool IsZero2D() const
	{
		return x == 0.0f && y == 0.0f;
	}

public:
	int ix() const
	{
		return static_cast<int>(x);
	}

	int iy() const
	{
		return static_cast<int>(y);
	}

	int iz() const
	{
		return static_cast<int>(z);
	}

	int iw() const
	{
		return static_cast<int>(w);
	}

	int hix() const
	{
		return static_cast<int>(x * 0.5f);
	}

	int hiy() const
	{
		return static_cast<int>(y * 0.5f);
	}

	int hiz() const
	{
		return static_cast<int>(z * 0.5f);
	}

	float4 Half() const
	{
		return { x * 0.5f, y * 0.5f , z * 0.5f, 1.0f };
	}

	float4 operator-(const float4& _Other) const
	{
		return { x - _Other.x, y - _Other.y, z - _Other.z, 1.0f };
	}

	float4 operator+(const float4& _Other) const
	{
		return { x + _Other.x, y + _Other.y, z + _Other.z, 1.0f };
	}

	float4 operator*(const float4& _Other) const
	{
		return { x * _Other.x, y * _Other.y, z * _Other.z, 1.0f };
	}


	float4& operator+=(const float4& _Other)
	{
		x += _Other.x;
		y += _Other.y;
		z += _Other.z;

		return *this;
	}

public:

	// 인자를 받지 않고 생성하면 0.0f로 초기화 
	float4()
		: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{

	}

	// x와 y인자를 받으면 그 인자값으로 x,y값 초기화
	float4(float _x, float _y)
		: x(_x), y(_y), z(0.0f), w(1.0f)
	{

	}

	// x, y z 인자를 받으면 그 인자값으로 x,y,z값 초기화
	float4(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z), w(1.0f)
	{

	}

	// x, y z,w 인자를 받으면 그 인자값으로 x,y,z,w값 초기화
	float4(float _x, float _y, float _z, float _w)
		: x(_x), y(_y), z(_z), w(_w)
	{

	}



};

struct GameEngineRect
{
public:
	float4 Pos;
	float4 Scale;

public:

	// 왼쪽으로 반만큼 이동
	int CenterLeft()
	{
		return Pos.ix() - Scale.hix();
	}

	// 오른쪽으로 반만큼 이동
	int CenterRight()
	{
		return Pos.ix() + Scale.hix();
	}

	// 위쪽으로 반만큼 이동
	int CenterTop()
	{
		return Pos.iy() - Scale.hiy();
	}

	// 아래쪽으로 반만큼 이동
	int CenterBot()
	{
		return Pos.iy() + Scale.hiy();
	}

public:
	GameEngineRect(float4 _Pos, float4 _Scale)
		: Pos(_Pos)
		, Scale(_Scale)
	{

	}
};
