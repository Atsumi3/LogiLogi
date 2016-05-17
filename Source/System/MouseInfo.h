#pragma once
#include "../UI/Enum/EnumMouseClickKind.h"
#include "../UI/Enum/EnumMouseDragDirection.h"

class MouseInfo
{
public:
	// �}�E�X���h���b�O���Ă���s
	int draggingRow = -1;
	int draggingCol = -1;
	bool pressedRight = false;
	EnumMouseClickKind draggingState = EnumMouseClickKindNONE;
	EnumMouseDragDirection draggingDirection = EnumMouseDragDirectionNONE;

	void reset()
	{
		pressedRight = false;
		draggingCol = -1;
		draggingRow = -1;
		draggingState = EnumMouseClickKindNONE;
		draggingDirection = EnumMouseDragDirectionNONE;
	}
};
