#pragma once

enum class RenderPivot // pivot 기준점
{
	CENTER,
	BOT,
};

enum class RenderScaleMode
{
	Image, // 실제 이미지 크기로
	User, // 내가 정한 크기로
};