#pragma once
#include <string>
#include <algorithm>

class GameEngineString // string과 관련된 문자열 처리 함수 모음
{
public:
	static void ToUpper(std::string& _Text)
	{
		std::transform(_Text.begin(), _Text.end(), _Text.begin(), std::toupper);
	}

	static std::string ToUpperReturn(const std::string& _Text)
	{
		std::string NewText = _Text;
		std::transform(NewText.begin(), NewText.end(), NewText.begin(), std::toupper);
		return NewText;
	}


private:
	GameEngineString();
	~GameEngineString();

	GameEngineString(const GameEngineString& _other) = delete;
	GameEngineString(GameEngineString&& _other) = delete;
	GameEngineString& operator=(const GameEngineString& _other) = delete;
	GameEngineString& operator=(GameEngineString&& _other) noexcept = delete;

};

