#pragma once
#include "../UI/UIPictPanel.h"
#include "MouseInfo.h"

class GameManager
{
public:

	MouseInfo GlobalMouseInfo;

	UIPictPanel PictPanel;

	void Draw();

	GameManager();
};
