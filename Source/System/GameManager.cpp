#include "GameManager.h"
#include "../Util/MathUtil.h"
#include "../Global.h"

void GameManager::Init()
{
	const int margin = 16;
	const int smaller = MathUtil::smaller(GAME_SIZE.width, GAME_SIZE.height) / 1.5;

	float ratio = 4;
	int wid = this->relativeFrame.minY() + this->relativeFrame.size.width / 4;
	int hgt = this->relativeFrame.minY() + this->relativeFrame.size.height / 4;
		
	PictPanel = UIPictPanel(&GlobalMouseInfo, 
		Rect(wid, hgt,
		this->relativeFrame.maxX() - wid,
		this->relativeFrame.maxY() - hgt ));
}

void GameManager::Draw()
{
	PictPanel.Update();
}
