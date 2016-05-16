#include "DxLib.h"
#include "UI/Common/Size.h"
#include "UI/Common/UIView.h"
#include "Util/FpsManager.h"

const Size windowSize = Size(640, 480);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(windowSize.width, windowSize.height, 32);
	SetAlwaysRunFlag(TRUE);
	SetBackgroundColor(0, 0, 0);
	ChangeWindowMode(true);

	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	FpsManager fpsManager;

	// 表示するビュー
	UIView view = UIView(Rect(16, 16, 100, 50));

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		fpsManager.Update();

		view.Update();

		fpsManager.Wait();
	}

	DxLib_End();
	return 0;
}