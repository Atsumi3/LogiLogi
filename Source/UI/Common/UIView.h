#pragma once
#include "Rect.h"
#include <DxLib.h>
#include <vector>
#include "../Enum/EnumMouseClickKind.h"

// いろいろなViewのベースとなるView
class UIView
{
public:
	virtual ~UIView()
	{
	}

	///////////// View ///////////////
	// 親View
	UIView* parent = nullptr;
	// 子View達
	std::vector<UIView*> subViews;
	// Viewの絶対位置
	Rect originalFrame;
	// Viewの親との相対位置
	Rect relativeFrame;
	//////////////////////////////////

	/////////// Viewの設定 ///////////
	// ユーザーからのアクションに反応するか
	bool enabled = true;
	// ユーザーのタップに反応するか
	bool userInteractionEnabled = true;
	// 表示をするか (親がhiddenなら"子供もhidden" ではなく表示しない
	bool hidden = false;
	//////////////////////////////////

	//////// レイアウトの設定 ////////
	// 背景色(デフォルトは白
	int backgroundColor = GetColor(255, 255, 255);
	// 背景色の透明度 (デフォルトは透明にしない
	int backgroundAlpha = 0xFF;
	//////////////////////////////////

	///////// マウスの状態 ///////////
	// マウスカーソルがViewの上にあるか
	bool isMouseOver = false;
	// マウスにクリックされているか(右も左も)
	bool isMouseClicking = false;
	// マウスクリックの種類
	EnumMouseClickKind mouseClickingKind = EnumMouseClickKindNONE;
	//////////////////////////////////

	///////// コンストラクタ /////////
	UIView(){}
	UIView(Rect frame);
	//////////////////////////////////

	/// 毎フレーム毎に呼ばれる処理 ///
	// 親から呼ばれる処理
	void Update();
	//////////////////////////////////

	//////////// メソッド ////////////
	// 子ビューを追加
	void addSubView(UIView* view);
	//////////////////////////////////

	//////// イベントセット //////////
	/// * マウスカーソルが上にあるときのイベント
	// マウスカーソルが一番最初に上に乗った時
	void setOnMouseOverBeginCallback(void(*beginMouseOverCallback)(UIView*));
	// マウスカーソルが上に乗っている時
	void setOnMouseOverWhileCallback(void(*whileMouseOverCallback)(UIView*));
	// マウスカーソルが上から離れた時
	void setOnMouseOverEndCallback(void(*endMouseOverCallback)(UIView*));

	/// * マウスにクリックされた時のイベント
	// マウスにクリックされた時
	void setOnMouseClickBeginCallback(void(*beginMouseClickCallback)(UIView*, EnumMouseClickKind));
	// マウスにクリックされている時 (ホールド)
	void setOnMouseClickWhileCallback(void(*whileMouseClickCallback)(UIView*, EnumMouseClickKind));
	// マウスのクリックが終わった時
	void setOnMouseClickEndCallback(void(*endMouseClickCallback)(UIView*, EnumMouseClickKind));
	//////////////////////////////////
protected:

	// 描画関数
	virtual void Draw() const;
	void BackDraw() const;

private:
	////// 前フレームの状態保持 //////
	bool isMouseOverBeforeFrame = false;
	bool isMouseClickBeforeFrame = false;
	//////////////////////////////////

	/// 毎フレーム毎に呼ばれる処理 ///
	// 親との情報を更新する
	void UpdateRelativeParent();
	// マウスが上にあるかチェックする
	void CheckMouseOver();
	// マウスにクリックされているかチェックする
	void CheckMouseClick();
	//////////////////////////////////
	
	// イベントリスナ
	void(*beginMouseOverCallback)(UIView*) = nullptr;
	void(*whileMouseOverCallback)(UIView*) = nullptr;
	void(*endMouseOverCallback)(UIView*) = nullptr;

	void(*beginMouseClickCallback)(UIView*, EnumMouseClickKind) = nullptr;
	void(*whileMouseClickCallback)(UIView*, EnumMouseClickKind) = nullptr;
	void(*endMouseClickCallback)(UIView*, EnumMouseClickKind) = nullptr;
	//////////////////////////////////
};
