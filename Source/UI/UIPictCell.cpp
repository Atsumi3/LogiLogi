#include "UIPictCell.h"
#include "Util/UIUtil.h"

void UIPictCell::Init()
{
	this->setOnMouseClickBeginCallback(onClickBeginCallback);
	this->setOnMouseOverWhileCallback(onOverWhileCallback);
}

void UIPictCell::onOverWhileCallback(UIView* view)
{
	UIPictCell* cell = static_cast<UIPictCell *>(view);
	if(!cell->isSelectBorderEnable)
	{
		return;
	}
	const int borderLineColor = cell->borderColor;
	const int middleBorderLineColor = cell->borderColor - 0x101010;
	// 上の横線
	DrawLine(
		cell->relativeFrame.minX(),
		cell->relativeFrame.minY() + cell->borderWidth / 2,
		cell->relativeFrame.maxX(),
		cell->relativeFrame.minY() + cell->borderWidth / 2,
		borderLineColor, cell->borderWidth);


	// 左の縦線
	DrawLine(
		cell->relativeFrame.minX() + cell->borderWidth / 2,
		cell->relativeFrame.minY(),
		cell->relativeFrame.minX() + cell->borderWidth / 2,
		cell->relativeFrame.maxY(),
		borderLineColor, cell->borderWidth);

	// 下の横線
	DrawLine(
		cell->relativeFrame.minX(),
		cell->relativeFrame.maxY() - cell->borderWidth / 2,
		cell->relativeFrame.maxX(),
		cell->relativeFrame.maxY() - cell->borderWidth / 2,
		borderLineColor, cell->borderWidth);

	// 右の縦線
	DrawLine(
		cell->relativeFrame.maxX() - cell->borderWidth / 2,
		cell->relativeFrame.minY(),
		cell->relativeFrame.maxX() - cell->borderWidth / 2,
		cell->relativeFrame.maxY(), 
		borderLineColor, cell->borderWidth);

	//##------------------------------------------------------

	// 左上の線
	// 左上のボックス
	DrawFillBox(
		cell->relativeFrame.minX(), 
		cell->relativeFrame.minY(), 
		cell->relativeFrame.minX() + 1, 
		cell->relativeFrame.minY() + 1, 
		middleBorderLineColor);
	DrawLine(
		cell->relativeFrame.minX() + 1,
		cell->relativeFrame.minY() + 1,
		cell->relativeFrame.minX() + cell->borderWidth + 1,
		cell->relativeFrame.minY() + cell->borderWidth + 1,
		middleBorderLineColor, sqrt(cell->borderWidth));

	// 右下の線
	// 右下のボックス
	DrawFillBox(
		cell->relativeFrame.maxX() - 2,
		cell->relativeFrame.maxY() - 2,
		cell->relativeFrame.maxX(),
		cell->relativeFrame.maxY(),
		middleBorderLineColor);
	DrawLine(
		cell->relativeFrame.maxX() - cell->borderWidth - 1,
		cell->relativeFrame.maxY() - cell->borderWidth - 1,
		cell->relativeFrame.maxX() - 1,
		cell->relativeFrame.maxY() - 1,
		middleBorderLineColor, sqrt(cell->borderWidth));

	// 左下の線
	// 左下のボックス
	DrawFillBox(
		cell->relativeFrame.minX(),
		cell->relativeFrame.maxY() - 2,
		cell->relativeFrame.minX() + 2,
		cell->relativeFrame.maxY(),
		middleBorderLineColor);
	DrawLine(
		cell->relativeFrame.minX() + 1,
		cell->relativeFrame.maxY() - 1,
		cell->relativeFrame.minX() + cell->borderWidth + 1,
		cell->relativeFrame.maxY() - cell->borderWidth - 1,
		middleBorderLineColor, sqrt(cell->borderWidth));

	DrawFillBox(
		cell->relativeFrame.maxX() - 2,
		cell->relativeFrame.minY() + 2,
		cell->relativeFrame.maxX(),
		cell->relativeFrame.minY(),
		middleBorderLineColor);
	DrawLine(
		cell->relativeFrame.maxX() - cell->borderWidth - 1,
		cell->relativeFrame.minY() + cell->borderWidth + 1,
		cell->relativeFrame.maxX() - 1,
		cell->relativeFrame.minY() + 1,
		middleBorderLineColor, sqrt(cell->borderWidth));
}

void UIPictCell::onClickBeginCallback(UIView* view, EnumMouseClickKind clickKind)
{
	UIPictCell* cell = static_cast<UIPictCell *>(view);

	if (cell->state != EnumPictCellStateNONE && cell->state != EnumPictCellStateKEEP && cell->state != EnumPictCellStateQUESTION)
	{
	} else {
		// 左クリック
		if (clickKind == EnumMouseClickKindLEFT)
		{
			// 正解だったらOPEN 違ったらCLOSE
			cell->state = cell->isPoint ? EnumPictCellStateOPEN : EnumPictCellStateEND;
		} else if (clickKind == EnumMouseClickKindRIGHT)
		{
			// 右クリック
			if (!cell->GlobalMouseInfo->pressingRight)
			{
				// 初めて右クリックを始めた時
				cell->GlobalMouseInfo->pressingRight = true;
				EnumPictCellState newState =
					cell->state == EnumPictCellStateNONE ? EnumPictCellStateKEEP :
					cell->state == EnumPictCellStateKEEP ? EnumPictCellStateQUESTION :
					cell->state == EnumPictCellStateQUESTION ? EnumPictCellStateNONE : EnumPictCellStateNONE;
				cell->state = newState;

				cell->GlobalMouseInfo->draggingState = newState;
				cell->GlobalMouseInfo->draggingCol = cell->cellIndexCol;
				cell->GlobalMouseInfo->draggingRow = cell->cellIndexRow;
			} else
			{
				// 既に右クリックされてる時
				if(cell->cellIndexCol == cell->GlobalMouseInfo->draggingCol && cell->cellIndexRow == cell->GlobalMouseInfo->draggingRow ||
					cell->cellIndexCol != cell->GlobalMouseInfo->draggingCol && cell->cellIndexRow != cell->GlobalMouseInfo->draggingRow)
				{
				} else
				{
					// 開始時とどっちかの座標が違うとき
					switch(cell->GlobalMouseInfo->draggingDirection)
					{
					case EnumMouseDragDirectionNONE: 
						// はじめてのドラッグ
						if (cell->cellIndexCol != cell->GlobalMouseInfo->draggingCol && cell->cellIndexRow == cell->GlobalMouseInfo->draggingRow)
						{
							cell->GlobalMouseInfo->draggingDirection = EnumMouseDragDirectionVERTICAL;
						} else if (cell->cellIndexCol == cell->GlobalMouseInfo->draggingCol && cell->cellIndexRow != cell->GlobalMouseInfo->draggingRow)
						{
							cell->GlobalMouseInfo->draggingDirection = EnumMouseDragDirectionHORIZONTAL;
						}
						cell->state = cell->GlobalMouseInfo->draggingState;
						break;
					case EnumMouseDragDirectionHORIZONTAL: 
						// 横に移動している場合
						if (cell->cellIndexCol == cell->GlobalMouseInfo->draggingCol && cell->cellIndexRow != cell->GlobalMouseInfo->draggingRow)
						{
							cell->state = cell->GlobalMouseInfo->draggingState;
						}
						break;
					case EnumMouseDragDirectionVERTICAL: 
						// 縦に移動してる場合
						if (cell->cellIndexCol != cell->GlobalMouseInfo->draggingCol && cell->cellIndexRow == cell->GlobalMouseInfo->draggingRow)
						{
							cell->state = cell->GlobalMouseInfo->draggingState;
						}
						break;
					default: break;
					}
				}
			}
		} else
		{
			cell->GlobalMouseInfo->resetDragging();
		}
	}
}

void UIPictCell::drawFillFrame(int Color) const
{
	DrawBox(relativeFrame.minX(), relativeFrame.minY(), relativeFrame.maxX(), relativeFrame.maxY(), Color, TRUE);
}

void UIPictCell::setCellIndex(int row, int col)
{
	this->cellIndexRow = row;
	this->cellIndexCol = col;
}

void UIPictCell::Draw()
{
	Point p;

	// 交互に背景色を変える
	if ((cellIndexRow + cellIndexCol) % 2 == 0)
	{
		this->drawFillFrame(0xdbffdb);
	}
	else
	{
		this->drawFillFrame(0xffdbff);
	}

	// それぞれのセルの状態の時の表示
	switch(this->state)
	{
	case EnumPictCellStateNONE: break;
	case EnumPictCellStateOPEN:
		this->drawFillFrame(selectedColor);
		break;
	case EnumPictCellStateKEEP: 
		p = UIUtil::CalcAlignCenterText(this->relativeFrame, "×");
		DrawString(p.x, p.y, "×", GetColor(0, 0, 0));
		break;
	case EnumPictCellStateQUESTION:
		p = UIUtil::CalcAlignCenterText(this->relativeFrame, "？");
		DrawString(p.x, p.y, "？", GetColor(0, 0, 0));
		break;
	case EnumPictCellStateEND:
		this->drawFillFrame(0x808080);
		break;
	default: break;
	}
}
