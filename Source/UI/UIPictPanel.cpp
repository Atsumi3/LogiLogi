#include "UIPictPanel.h"
#include <algorithm>

void UIPictPanel::Draw()
{
	// --------------------- セルを塗る -------------------
	for (int row = 0; row < rowPanelNum; row++)
	{
		for (int col = 0; col < colPanelNum; col++)
		{
			this->panelGroup[row][col].Update();
		}
	}

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

void UIPictPanel::Init()
{
	const int big = 
		this->relativeFrame.size.width > this->relativeFrame.size.height ?
		this->relativeFrame.size.height : this->relativeFrame.size.width;

	this->panelSizeRect = big / (colPanelNum > rowPanelNum ?  colPanelNum : rowPanelNum);

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
			this->panelGroup[i][k] = p;
		}
	}
}
