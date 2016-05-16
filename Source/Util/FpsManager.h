#pragma once

#define FPS 60

class FpsManager
{
private:
	int mStartTime;
	int mCount;
	float mFps;

public:
	FpsManager()
	{
		mStartTime = 0;
		mCount = 0;
		mFps = 0;
	}

	// フレーム更新用
	bool Update();

	// Fps調整
	void Wait() const;
};
