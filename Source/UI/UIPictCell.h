#pragma once
#include "Common/UIView.h"
#include "Enum/EnumPictCellState.h"

class UIPictCell : public UIView
{
private:
	void Init();

	static void onOverWhileCallback(UIView* view);
	static void onClickBeginCallback(UIView* view, EnumMouseClickKind clickKind);
public:
	virtual ~UIPictCell()
	{
	}

	// セルの状態を保存
	EnumPictCellState state = EnumPictCellStateNONE;

	int borderWidth = 8;
	int borderColor = 0x30FF30;

	// セルが正解のセルかどうか
	bool isPoint = false;

	UIPictCell()
	{
		this->Init();
	}
	UIPictCell(Rect rect);

	void Draw() const override;
};
