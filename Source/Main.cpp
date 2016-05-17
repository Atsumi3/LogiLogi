#include "DxLib.h"
#include "Global.h"
#include "Util/FpsManager.h"
#include "System/GameManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(GAME_SIZE.width, GAME_SIZE.height, 32);
	SetAlwaysRunFlag(TRUE);
	SetBackgroundColor(255, 255, 255);
	ChangeWindowMode(true);

	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	FpsManager fpsManager;
	GameManager gameManager;

	// 表示するビュー

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		fpsManager.Update();
		gameManager.Draw();
		fpsManager.Wait();
	}

	DxLib_End();
	return 0;
}