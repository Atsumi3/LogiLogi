#include "UIView.h"
#include <DxLib.h>
#include <ostream>
#include <algorithm>
#include <iostream>

UIView::UIView(Rect frame)
{
	this->originalFrame = frame;
	this->relativeFrame = frame;
	this->subViews = std::vector<UIView*>(0);
}

void UIView::Update()
{
	this->UpdateRelativeParent();
	if (!hidden && (!parent || parent && !parent->hidden)) {
		this->CheckMouseOver();
		this->CheckMouseClick();
		this->Draw();
	}

	std::for_each(begin(subViews), end(subViews), [](UIView* &i) {
		i->Update();
	});
}

void UIView::addSubView(UIView* view)
{
	view->parent = this;
	this->subViews.push_back(view);
}

///////// イベント発火 ///////////
/// * マウスカーソルが上にあるときのイベント
// マウスカーソルが一番最初に上に乗った時
void UIView::setOnMouseOverBeginCallback(void(* beginMouseOverCallback)(UIView*))
{
	this->beginMouseOverCallback = beginMouseOverCallback;
}

// マウスカーソルが上に乗っている時
void UIView::setOnMouseOverWhileCallback(void(* whileMouseOverCallback)(UIView*))
{
	this->whileMouseOverCallback = whileMouseOverCallback;
}

// マウスカーソルが上から離れた時
void UIView::setOnMouseOverEndCallback(void(* endMouseOverCallback)(UIView*))
{
	this->endMouseOverCallback = endMouseOverCallback;
}

/// * マウスにクリックされた時のイベント
// マウスに一番最初にクリックされた時
void UIView::setOnMouseClickBeginCallback(void(* beginMouseClickCallback)(UIView*, EnumMouseClickKind))
{
	this->beginMouseClickCallback = beginMouseClickCallback;
}

// マウスにクリックされている時 (ホールド)
void UIView::setOnMouseClickWhileCallback(void(*whileMouseClickCallback)(UIView*, EnumMouseClickKind))
{
	this->whileMouseClickCallback = whileMouseClickCallback;
}

// マウスのクリックが終わった時
void UIView::setOnMouseClickEndCallback(void(*endMouseClickCallback)(UIView*, EnumMouseClickKind))
{
	this->endMouseClickCallback = endMouseClickCallback;
}

// 描画処理
void UIView::Draw() const
{
	// 背景描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, backgroundAlpha);
	DrawFillBox(
		relativeFrame.minX(), relativeFrame.minY(),
		relativeFrame.maxX(), relativeFrame.maxY(), backgroundColor);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//////////////////////////////////

// 親との情報を更新する
void UIView::UpdateRelativeParent()
{
	if (this->parent)
	{
		// 座標情報の更新
		relativeFrame.point.x = 
			parent->relativeFrame.minX() + originalFrame.minX();
		relativeFrame.point.y =
			parent->relativeFrame.minY() + originalFrame.minY();
	}
	// オリジナルのサイズを更新
	relativeFrame.size = originalFrame.size;
}

// マウスが領域の上にあるかチェックする
void UIView::CheckMouseOver()
{
	// マウスの座標取得
	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);

	// マウスの座標がオブジェクトの領域に入っているか
	this->isMouseOver =
		mouseX >= this->relativeFrame.minX() && 
		this->relativeFrame.maxX() > mouseX &&
		mouseY >= this->relativeFrame.minY() && 
		this->relativeFrame.maxY() > mouseY;

	if (this->isMouseOver)
	{ // マウスが領域に入っている
		// 前のフレームでマウスが領域に入っているか
		if (!isMouseOverBeforeFrame)
		{
			// 前のフレームで領域に入っていなかった時 (最初)
			this->isMouseOverBeforeFrame = true;
			if (this->beginMouseOverCallback && enabled)
			{
				// イベント
				this->beginMouseOverCallback(this);
			}
		}
		else
		{
			// 前のフレームでも領域に入っていた時 (最中)
			// while
			if (this->whileMouseOverCallback && enabled)
			{
				this->whileMouseOverCallback(this);
			}
		}
	}
	else
	{
		// マウスが領域に入っていない
		if (isMouseOverBeforeFrame && this->endMouseOverCallback && enabled)
		{
			// 前のフレームはマウスが領域に入っていた時 (最後)
			this->endMouseOverCallback(this);
		}
		this->isMouseOverBeforeFrame = false;
	}
}

// マウスにクリックされているかチェックする
void UIView::CheckMouseClick()
{
	// マウスが領域の上にない時
	if(!isMouseOver)
	{
		isMouseClicking = false;
		if(isMouseClickBeforeFrame && endMouseClickCallback && enabled && userInteractionEnabled)
		{
			this->endMouseClickCallback(this, mouseClickingKind);
		}
		isMouseClickBeforeFrame = false;
		mouseClickingKind = EnumMouseClickKind::NONE;
		return;
	}
	// マウスにクリックされているか 且つ マウスが上にあるか
	int Mouse = GetMouseInput();
	this->mouseClickingKind =
		Mouse & MOUSE_INPUT_LEFT ? EnumMouseClickKind::LEFT :
		Mouse & MOUSE_INPUT_RIGHT ? EnumMouseClickKind::RIGHT :
		Mouse & MOUSE_INPUT_MIDDLE ? EnumMouseClickKind::CENTER : EnumMouseClickKind::NONE;
	this->isMouseClicking = mouseClickingKind != EnumMouseClickKind::NONE;

	if (this->isMouseClicking)
	{ // クリックされている
	  // 前のフレームでクリックされているか
		if (!isMouseClickBeforeFrame)
		{
			// 前のフレームでクリックされていない (最初)
			isMouseClickBeforeFrame = true;
			if (this->beginMouseClickCallback && enabled && userInteractionEnabled)
			{
				this->beginMouseClickCallback(this, mouseClickingKind);
			}
		}
		else
		{
			// 前のフレームでクリックされている (最中)
			if (this->whileMouseClickCallback && enabled && userInteractionEnabled)
			{
				this->whileMouseClickCallback(this, mouseClickingKind);
			}
		}
	}
	else
	{
		// クリックされていない
		if (isMouseClickBeforeFrame && this->endMouseClickCallback && enabled && userInteractionEnabled)
		{
			// 前のフレームでクリックされている (最後)
			this->endMouseClickCallback(this, mouseClickingKind);
		}
		isMouseClickBeforeFrame = false;
	}
}
