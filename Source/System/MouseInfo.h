#pragma once
#include "../UI/Enum/EnumMouseClickKind.h"
#include "../UI/Enum/EnumMouseDragDirection.h"

class MouseInfo
{
public:
	// �}�E�X���h���b�O���Ă���s
	int draggingRow = -1;
	int draggingCol = -1;
	bool pressingRight = false;
	EnumPictCellState draggingState = EnumPictCellStateNONE;
	EnumMouseDragDirection draggingDirection = EnumMouseDragDirectionNONE;

	void reset()
	{
		pressingRight = false;
		draggingCol = -1;
		draggingRow = -1;
		draggingState = EnumPictCellStateNONE;
		draggingDirection = EnumMouseDragDirectionNONE;
	}
};
