#pragma once
#include "Common/UIView.h"
#include "Enum/EnumPictCellState.h"
#include "../System/MouseInfo.h"

class UIPictCell : public UIView
{
private:
	void Init();

	// マウスが上にあるときコールバック
	static void onOverWhileCallback(UIView* view);
	// マウスでクリックしてる時のコールバック
	static void onClickBeginCallback(UIView* view, EnumMouseClickKind clickKind);
	// 背景色を塗る
	void drawFillFrame(int Color) const;
public:
	virtual ~UIPictCell()
	{
	}
	// MouseInfo
	MouseInfo* GlobalMouseInfo = nullptr;

	// 自分のインデックスを保存
	int cellIndexRow = 0;
	int cellIndexCol = 0;

	// セルの状態を保存
	EnumPictCellState state = EnumPictCellStateNONE;

	// セルが正解のセルかどうか
	bool isPoint = false;

	// 選択中の色
	int selectedColor = 0xffbf7f;

	// 選択中の線を表示するかどうか
	bool isSelectBorderEnable = false;
	int borderWidth = 1;
	int borderColor = 0x7F7F7F;

	UIPictCell()
	{
		this->Init();
	}
	
	UIPictCell(Rect rect) : UIView(rect)
	{
		this->Init();
	}

	void setCellIndex(int row, int col);

	void Draw() override;
};
