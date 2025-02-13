﻿#include "UIPictPanel.h"
#include <algorithm>
#include "Util/UIUtil.h"
#include "../Global.h"

vector<int> UIPictPanel::rToVec(vector<int> r) const
{
	vector<int> arr;
	int renzoku = 0;
	for (int i = 0; i < r.size(); i++)
	{
		if (r[i] == 0)
		{
			if (renzoku > 0)
			{
				arr.push_back(renzoku);
				renzoku = 0;
			}
		}
		else
		{
			renzoku += 1;
		}
	}
	if (renzoku > 0)
	{
		arr.push_back(renzoku);
		renzoku = 0;
	}

	return arr;
}

void UIPictPanel::UpdateFontSize(int fontSize)
{
	this->fontSize = fontSize;
	this->font = CreateFontToHandle(NULL, fontSize, 1);
}

void UIPictPanel::Draw()
{
	// --------------------- セルを塗る -------------------
	bool isExistTappingView = false;
	bool isExistHoveringView = false;
	for (int row = 0; row < rowPanelNum; row++)
	{
		for (int col = 0; col < colPanelNum; col++)
		{
			// セルのアップデート(描画)
			this->panelGroup[row][col].Update();

			// タップしているビューがあるかチェック
			if (!isExistTappingView) {
				isExistTappingView = this->panelGroup[row][col].isMouseClicking;
			}

			// マウスの下にセルがあるかチェック
			if (!isExistHoveringView && this->panelGroup[row][col].isMouseOver)
			{
				isExistHoveringView = true;
				GlobalMouseInfo->hoveringCol = col;
				GlobalMouseInfo->hoveringRow = row;
			}
		}
	}

	// タップしているビューが無かったらマウス情報をリセット
	if (!isExistTappingView && GlobalMouseInfo)
	{
		GlobalMouseInfo->resetDragging();
	}

	// マウスがどのセルの上にもいなかったらリセット
	if (!isExistHoveringView && GlobalMouseInfo)
	{
		GlobalMouseInfo->resetHovering();
	}

	// ドラッグ中だったら暗くする
	if(GlobalMouseInfo && this->GlobalMouseInfo->draggingDirection != EnumMouseDragDirectionNONE)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
		if(this->GlobalMouseInfo->draggingDirection == EnumMouseDragDirectionHORIZONTAL)
		{
			// 横にドラッグしてる時
			// ドラッグしている行以外の行に黒いマスクをつける
			
			// 上のボックス
			DrawBox(relativeFrame.minX(),
				relativeFrame.minY(),
				relativeFrame.maxX(),
				relativeFrame.minY() + (GlobalMouseInfo->draggingCol) * this->panelSizeRect, GetColor(20, 20, 20), TRUE);
			// 下のボックス
			DrawBox(relativeFrame.minX(),
				relativeFrame.minY() + (GlobalMouseInfo->draggingCol + 1) * this->panelSizeRect,
				relativeFrame.maxX(),
				relativeFrame.maxY()
				, GetColor(20, 20, 20), TRUE);
		} else if (this->GlobalMouseInfo->draggingDirection == EnumMouseDragDirectionVERTICAL)
		{
			// 縦にドラッグしてる時
			// ドラッグしている列以外の列に黒いマスクをつける

			// 左のボックス
			DrawBox(relativeFrame.minX(),
				relativeFrame.minY(),
				relativeFrame.minX() + GlobalMouseInfo->draggingRow * this->panelSizeRect,
				relativeFrame.maxY(), GetColor(20, 20, 20), TRUE);

			// 右のボックス
			DrawBox(relativeFrame.minX() + (GlobalMouseInfo->draggingRow + 1) * this->panelSizeRect,
				relativeFrame.minY(),
				relativeFrame.maxX(),
				relativeFrame.maxY(), GetColor(20, 20, 20), TRUE);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	// よこ
	for (int row = 0; row < rowPanelNum; row++)
	{
		vector<int> r = vector<int>(this->colPanelNum, 0);
		for (int col = 0; col < colPanelNum; col++)
		{
			r[col] = panelGroup[row][col].isPoint ? 1 : 0;
		}
		vector<int> arr = rToVec(r);
		char const* str = "---";
		const int marginBottom = 4;
		const int bW = relativeFrame.minX() + (row * panelSizeRect);
		const int w = int(bW + (bW + panelSizeRect - bW) / 2 - GetDrawStringWidthToHandle(str, strlen(str), font) / 2);
		if (arr.size() == 0)
		{
			DrawFormatStringToHandle(w, relativeFrame.minY() - marginBottom - fontSize, countColor, font, "%2d", 0);
		}
		else {
			for (int i = 0; i < arr.size(); i++)
			{
				DrawFormatStringToHandle(w, relativeFrame.minY() - marginBottom - fontSize * (i + 1), countColor, font, "%2d", arr[arr.size() - (i + 1)]);
			}
		}
	}

	// たて
	for (int col = 0; col < colPanelNum; col++)
	{
		vector<int> r = vector<int>(this->rowPanelNum, 0);
		for (int row = 0; row < rowPanelNum; row++)
		{
			r[row] = panelGroup[row][col].isPoint ? 1 : 0;
		}
		vector<int> arr = rToVec(r);
		char const* str = "---";
		const int marginBottom = 4;
		const int bW = relativeFrame.minY() + (col * panelSizeRect);
		const int w = int(bW + (bW + panelSizeRect - bW) / 2 - GetDrawStringWidthToHandle(str, strlen(str), font) / 2);
		if (arr.size() == 0)
		{
			DrawFormatStringToHandle(relativeFrame.minX() - marginBottom - fontSize, w, countColor, font, "%2d", 0);
		}
		else {
			for (int i = 0; i < arr.size(); i++)
			{
				DrawFormatStringToHandle(relativeFrame.minX() - marginBottom - fontSize * (i + 1), w, countColor, font, "%2d", arr[arr.size() - (i + 1)]);
			}
		}
	}

//	if(GlobalMouseInfo->hoveringCol > -1)
//	{
//		// 横
//		Rect r = Rect(
//			relativeFrame.minX() - panelSizeRect, 
//			relativeFrame.minY() + (GlobalMouseInfo->hoveringCol * panelSizeRect), panelSizeRect, panelSizeRect);
//		Point p = UIUtil::CalcAlignCenterText(r, "x");
//		DrawString(p.x, p.y, "x", GetColor(0, 0, 0));
//
//
//		Rect r2 = Rect(
//			relativeFrame.minX() + GlobalMouseInfo->hoveringRow * panelSizeRect, 
//			relativeFrame.minY() - panelSizeRect, 
//			panelSizeRect, panelSizeRect);
//		Point p2 = UIUtil::CalcAlignCenterText(r2, "y");
//		DrawString(p2.x, p2.y, "y", GetColor(0, 0, 0));
//	}

	DrawLayerBorder();
}

// セルパネルの初期化
void UIPictPanel::Init()
{
	// マウス情報の初期化
	if (GlobalMouseInfo) {
		GlobalMouseInfo->resetDragging();
	}

	// セル描画のためにさいずを図ってる
	const int big = 
		this->relativeFrame.size.width > this->relativeFrame.size.height ?
		this->relativeFrame.size.height : this->relativeFrame.size.width;

	this->panelSizeRect = big / (colPanelNum > rowPanelNum ?  colPanelNum : rowPanelNum);

	this->UpdateFontSize(this->panelSizeRect / 2);

	this->panelGroup = vector<vector<UIPictCell>>(rowPanelNum, vector<UIPictCell>(colPanelNum));
	for (int i = 0; i< rowPanelNum; i++)
	{
		for (int k = 0; k < colPanelNum; k++)
		{
			const int posX = this->relativeFrame.minX() + (i * panelSizeRect);
			const int posY = this->relativeFrame.minY() + (k * panelSizeRect);
			UIPictCell p = UIPictCell(Rect(posX, posY, panelSizeRect, panelSizeRect));
			p.setCellIndex(i, k);
			p.GlobalMouseInfo = this->GlobalMouseInfo;
			p.isPoint = GetRand(100) % 3 == 0;
			this->panelGroup[i][k] = p;
		}
	}
	this->font = CreateFontToHandle("メイリオ", fontSize, 1);
}

void UIPictPanel::DrawLayerBorder() const
{
	// 外枠
	int lineColor = 0x000000;
	const int maxX = this->relativeFrame.minX() + rowPanelNum * panelSizeRect + 1;
	const int maxY = this->relativeFrame.minY() + colPanelNum * panelSizeRect + 1;

	// 上横線
	DrawLine(this->relativeFrame.minX() - (roundBorderWidth / 2),
		this->relativeFrame.minY(),
		maxX + (roundBorderWidth / 2),
		this->relativeFrame.minY(),
		lineColor, roundBorderWidth);

	// 左縦線
	DrawLine(this->relativeFrame.minX(),
		this->relativeFrame.minY(),
		this->relativeFrame.minX(),
		maxY,
		lineColor, roundBorderWidth);

	// 右縦線
	DrawLine(maxX,
		this->relativeFrame.minY(),
		maxX,
		maxY,
		lineColor, roundBorderWidth);

	// 舌横線
	DrawLine(this->relativeFrame.minX() - (roundBorderWidth / 2),
		maxY,
		maxX + (roundBorderWidth / 2),
		maxY,
		lineColor, roundBorderWidth);

	// 枠線描画
	for (int i = 0; i< rowPanelNum; i++)
	{
		for (int k = 0; k < colPanelNum; k++)
		{
			const int posX = this->relativeFrame.minX() + (i * panelSizeRect);
			const int posY = this->relativeFrame.minY() + (k * panelSizeRect);

			DrawLine(posX, this->relativeFrame.minY(), posX, maxY, lineColor, i % 5 == 0 ? roundBorderWidth / 2 : roundBorderWidth / 4);
			DrawLine(this->relativeFrame.minX(), posY, maxX, posY, lineColor, k % 5 == 0 ? roundBorderWidth / 2 : roundBorderWidth / 4);
		}
	}
}
