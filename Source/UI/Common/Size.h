#pragma once

// サイズクラス
class Size
{
public:
	unsigned int width = 0;
	unsigned int height = 0;

	Size() {};
	Size(unsigned int width, unsigned int height);
};