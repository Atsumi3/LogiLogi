#pragma once
#include "../Common/Rect.h"
#include <cstring>
#include <DxLib.h>

class UIUtil
{
public:
	// 文字と座標大きさを投げると文字を中心にするための座標を返す
	static Point CalcAlignCenterText(Rect rect, const char* str);
	static Point CalcAlignCenterText(Rect rect, const char* str, int fontHandle);
};
