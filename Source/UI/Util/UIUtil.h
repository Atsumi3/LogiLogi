#pragma once
#include "../Common/Rect.h"
#include <cstring>
#include <DxLib.h>

class UIUtil
{
public:
	static Point CalcAlignCenterText(Rect rect, const char* str);
	static Point CalcAlignCenterText(Rect rect, const char* str, int fontHandle);
};
