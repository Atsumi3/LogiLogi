#pragma once
#include "Common/UIView.h"
#include "UIPictCell.h"
#include "../System/MouseInfo.h"

using namespace std;

class UIPictPanel : public UIView
{
private:
	void Init();
	void DrawLayerBorder() const;

	vector<int> rToVec(vector<int> r) const;

	void UpdateFontSize(int fontSize);
public:

	// 周りの枠線の太さ Global.hへ
//	int roundBorderWidth = 4;
	// 周りの枠線の色
	int roundBorderColor = 0x202020;

	// 横パネルの数
	int rowPanelNum = 10;
	// 縦パネルの数
	int colPanelNum = 10;
	// フォントサイズ
	int fontSize = 15;
	// フォント
	int font = 0;
	// 文字色
	int countColor = 0x303030;

	// パネルの縦横幅
	int panelSizeRect = 0;

	// MouseInfo
	MouseInfo* GlobalMouseInfo = nullptr;

	// パネル格納
	vector<vector<UIPictCell>> panelGroup;
	
	// コンストラクタ
	UIPictPanel(){
		Init();
	}
	UIPictPanel(MouseInfo* GlobalMouseInfoPtr)
	{
		this->GlobalMouseInfo = GlobalMouseInfoPtr;
		Init();
	}
	UIPictPanel(MouseInfo* GlobalMouseInfoPtr, Rect rect) : UIView(rect)
	{
		this->GlobalMouseInfo = GlobalMouseInfoPtr;
		Init();
	}

	// デコンストラクタ
	virtual ~UIPictPanel()
	{
	}
	void Draw() override;
};
