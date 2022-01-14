#pragma once
#include "easyx.h"

struct Position
{
	unsigned int AxisX;
	unsigned int AxisY;
};

static struct GridColorSets
{
	COLORREF m_ColorLineWeight = 0xb0a7a7;
	COLORREF m_ColorLine = 0xd6d1d1;
	COLORREF m_ColorBGDefault = 0xc8fbcb;
	COLORREF m_ColorBGHover = 0xe1f6e2;
	COLORREF m_ColorText = 0x292222;
} colorSets;

/**
 * 控件-方格类 
 **/
class SquareGrid
{
private:
	unsigned short m_ID;
	Position m_Position;
	unsigned int m_SideLength;
	COLORREF m_CurrentBGColor;
	unsigned short m_Num;
	unsigned short m_NumMax;
public:
	SquareGrid(unsigned short id, Position initPosition, unsigned int sideLength, unsigned int num, unsigned int numMax);
	~SquareGrid();

	void Draw() const;
	void Hover(const ExMessage& msg);
	void Click(const ExMessage& msg);
	void AutoNum();
};