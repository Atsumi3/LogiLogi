#pragma once

typedef enum
{
	EnumPictCellStateNONE,	// 何も押してない時
	EnumPictCellStateOPEN,	// 開いた時
	EnumPictCellStateKEEP,	// 保留
	EnumPictCellStateQUESTION, // 候補
	EnumPictCellStateEND	// 開閉しきってる行列のCLOSE
} EnumPictCellState;
