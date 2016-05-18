#include "DxLib.h"
#include "Global.h"
#include "Util/FpsManager.h"
#include "System/GameManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(GAME_SIZE.width, GAME_SIZE.height, 32);
	SetAlwaysRunFlag(TRUE);
	SetBackgroundColor(0, 0, 0);
	ChangeWindowMode(true);

	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	FpsManager fpsManager;
	GameManager gameManager = GameManager(Rect(50, 50, 400, 400));
	gameManager.backgroundColor = 0xA0A0A0;

	// 表示するビュー
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		fpsManager.Update();
		gameManager.Update();
		fpsManager.Wait();
	}

	DxLib_End();
	return 0;
}