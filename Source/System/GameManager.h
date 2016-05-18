#pragma once
#include "../UI/UIPictPanel.h"
#include "MouseInfo.h"

class GameManager : public UIView
{
private:
	void Init();
public:
	MouseInfo GlobalMouseInfo;

	UIPictPanel PictPanel;

	void Draw() override;

	GameManager()
	{
		Init();
	}
	GameManager(Rect rect) : UIView(rect)
	{
		Init();
	}
};
