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
	if (clickKind == EnumMouseClickKindRIGHT)
	{
		switch (cell->state)
		{
		case EnumPictCellStateNONE: 
			cell->state = EnumPictCellStateKEEP;
			break;
		case EnumPictCellStateKEEP:
			cell->state = EnumPictCellStateQUESTION; 
			break;
		case EnumPictCellStateQUESTION:
			cell->state = EnumPictCellStateNONE;
			break;
		default: break;
		}
	} else if(clickKind == EnumMouseClickKindLEFT)
	{
		switch (cell->state)
		{
		case EnumPictCellStateNONE: 
			cell->state = EnumPictCellStateOPEN;
			break;
		case EnumPictCellStateOPEN:
			cell->state = EnumPictCellStateNONE;
			break;
		case EnumPictCellStateKEEP:
			cell->state = EnumPictCellStateOPEN;
			break;
		case EnumPictCellStateQUESTION: 
			cell->state = EnumPictCellStateOPEN;
			break;
		default: break;
		}
	}
}

UIPictCell::UIPictCell(Rect rect) : UIView(rect)
{
	this->Init();
}

void UIPictCell::Draw() const
{
	Point p;
	switch(this->state)
	{
	case EnumPictCellStateNONE: break;
	case EnumPictCellStateOPEN: 
		DrawLine(this->relativeFrame.minX(), this->relativeFrame.minY(),
			this->relativeFrame.maxX(), this->relativeFrame.maxY(), GetColor(0, 0, 0));

		DrawLine(this->relativeFrame.minX(), this->relativeFrame.maxY(),
			this->relativeFrame.maxX(), this->relativeFrame.minY(), GetColor(0, 0, 0));
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
		p = UIUtil::CalcAlignCenterText(this->relativeFrame, "");
		DrawString(p.x, p.y, "？", GetColor(0, 0, 0));
		break;
	default: break;
	}
}
