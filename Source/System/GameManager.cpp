#include "GameManager.h"
#include "../Util/MathUtil.h"
#include "../Global.h"

GameManager::GameManager()
{
	const int margin = 16;
	const int smaller = MathUtil::smaller(GAME_SIZE.width, GAME_SIZE.height) / 2;
	
	PictPanel = UIPictPanel(&GlobalMouseInfo, Rect(
		GAME_SIZE.width - smaller - margin,
		GAME_SIZE.height - smaller - margin,
		smaller, 
		smaller));
}

void GameManager::Draw()
{
	PictPanel.Update();
}
