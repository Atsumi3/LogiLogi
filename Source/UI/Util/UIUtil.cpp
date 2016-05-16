#include "UIUtil.h"

Point UIUtil::CalcAlignCenterText(Rect rect, const char* str)
{
	return CalcAlignCenterText(rect, str, -1);
}

Point UIUtil::CalcAlignCenterText(Rect rect, const char* str, int fontHandle)
{
	int fontW, fontH, lineC;
	if (fontHandle == -1) {
		GetDrawStringSize(&fontW, &fontH, &lineC, str, strlen(str));
	}
	else {
		GetDrawStringSizeToHandle(&fontW, &fontH, &lineC, str, strlen(str), fontHandle);
	}
	return Point(
		int(rect.minX() + (rect.maxX() - rect.minX()) / 2 - fontW / 2),
		int(rect.minY() + (rect.maxY() - rect.minY()) / 2 - fontH / 2));
}
