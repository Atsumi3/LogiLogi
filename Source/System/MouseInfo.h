#pragma once
#include "../UI/Enum/EnumMouseClickKind.h"
#include "../UI/Enum/EnumMouseDragDirection.h"

class MouseInfo
{
public:
	// マウスをドラッグしている行
	int draggingRow = -1;
	int draggingCol = -1;
	bool pressingRight = false;
	EnumPictCellState draggingState = EnumPictCellStateNONE;
	EnumMouseDragDirection draggingDirection = EnumMouseDragDirectionNONE;

	void resetDragging()
	{
		pressingRight = false;
		draggingCol = -1;
		draggingRow = -1;
		draggingState = EnumPictCellStateNONE;
		draggingDirection = EnumMouseDragDirectionNONE;
	}

	// マウスがセルの上にある状態
	int hoveringRow = -1;
	int hoveringCol = -1;

	void resetHovering()
	{
		hoveringCol = -1;
		hoveringRow = -1;
	}
};
