#pragma once

constexpr unsigned char GRID_SIZE = 60;
constexpr unsigned int GRID_SIDE_LENGTH = 60;
constexpr unsigned char GRID_COUNT_SINGLE = 9;
constexpr unsigned char GRID_NUM_MAX = 9;

constexpr unsigned int COLOR_BG = 0xc8fbcb;
constexpr unsigned int COLOR_BG_GRID_DEFAULT = 0xc8fbcb;
constexpr unsigned int COLOR_BG_GRID_HOVER = 0xe1f6e2;
constexpr unsigned int COLOR_LINE_NORMAL = 0xd6d1d1;
constexpr unsigned int COLOR_LINE_WEIGHT = 0xb0a7a7;
constexpr unsigned int COLOR_TEXT = 0x292222;

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
};

