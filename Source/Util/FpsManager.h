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

	// �t���[���X�V�p
	bool Update();

	// Fps����
	void Wait() const;
};
