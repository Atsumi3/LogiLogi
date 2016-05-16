#include "FpsManager.h"
#include <DxLib.h>

bool FpsManager::Update()
{
	if (mCount == 0) { //1フレーム目なら時刻を記憶
		mStartTime = GetNowCount();
	}
	if (mCount == FPS) { //60フレーム目なら平均を計算する
		int t = GetNowCount();
		mFps = 1000.f / ((t - mStartTime) / float(FPS));
		mCount = 0;
		mStartTime = t;
	}
	mCount++;
	return true;
}

void FpsManager::Wait() const
{
	int tookTime = GetNowCount() - mStartTime;	//かかった時間
	int waitTime = mCount * 1000 / FPS - tookTime;	//待つべき時間
	if (waitTime > 0) {
		Sleep(waitTime);	//待機
	}
}
