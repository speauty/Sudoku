#pragma once

constexpr unsigned char GRID_SIZE = 60;
constexpr unsigned int GRID_SIDE_LENGTH = 60;
constexpr unsigned char GRID_COUNT_SINGLE = 9;
constexpr unsigned char GRID_NUM_MAX = 9;

constexpr unsigned int COLOR_BG = 0xc8fbcb;
constexpr unsigned int COLOR_BG_GRID_DEFAULT = 0xc8fbcb;
constexpr unsigned int COLOR_BG_GRID_HOVER = 0xe1f6e2;
constexpr unsigned int COLOR_BG_GRID_LOCK = 0xc8fbaa;
;
constexpr unsigned int COLOR_LINE_NORMAL = 0xd6d1d1;
constexpr unsigned int COLOR_LINE_WEIGHT = 0xb0a7a7;
constexpr unsigned int COLOR_TEXT = 0x292222;
constexpr unsigned int COLOR_TEXT_BLOCK = 0xff006c;

constexpr unsigned char TIMER_COUNT = 5;
constexpr unsigned char TIMER_GRID_CLICK_CHAN = 0;
constexpr unsigned int TIMER_GRID_CLICK_DURATION = 300;



struct Position
{
	unsigned int AxisX;
	unsigned int AxisY;
};

struct PlaneCoordinate
{
	unsigned int AxisX;
	unsigned int AxisY;
};

struct SqureCell
{
	unsigned int id;
	PlaneCoordinate position;
	unsigned short val;
	bool locked;
};

static unsigned short SudokuTemplate1[GRID_COUNT_SINGLE][GRID_COUNT_SINGLE] = {
	{7, 2, 4, 5, 6, 1, 9, 3, 8},
	{6, 1, 9, 3, 8, 2, 5, 4, 7},
	{5, 3, 8, 9, 7, 4, 2, 6, 1},
	{2, 9, 3, 1, 4, 8, 6, 7, 5},
	{4, 8, 5, 6, 3, 7, 1, 2, 9},
	{1, 7, 6, 2, 9, 5, 4, 8, 3},
	{3, 4, 1, 7, 5, 6, 8, 9, 2},
	{9, 6, 2, 8, 1, 3, 7, 5, 4},
	{8, 5, 7, 4, 2, 9, 3, 1, 6},
};

static unsigned short SudokuTemplate[GRID_COUNT_SINGLE][GRID_COUNT_SINGLE] = {
	{7, 0, 0, 0, 0, 0, 9, 0, 0},
	{0, 1, 0, 3, 0, 0, 5, 0, 0},
	{0, 3, 8, 9, 0, 0, 2, 0, 1},
	{2, 0, 3, 0, 4, 8, 6, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 6, 2, 9, 0, 4, 0, 3},
	{3, 0, 1, 0, 0, 6, 8, 9, 0},
	{0, 0, 2, 0, 0, 3, 0, 5, 0},
	{0, 0, 7, 0, 0, 0, 0, 0, 6},
};

