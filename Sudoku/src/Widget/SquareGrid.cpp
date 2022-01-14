#include "SquareGrid.h"
#include "../Timer.hpp"
#include <wchar.h>

SquareGrid::SquareGrid(unsigned short id, Position initPosition, unsigned int sideLength, unsigned int num, unsigned int numMax)
	: m_ID(id), m_Position(initPosition), m_SideLength(sideLength), m_Num(num), m_NumMax(numMax)
{
	m_CurrentBGColor = colorSets.m_ColorBGDefault;
}

SquareGrid::~SquareGrid()
{
}

void SquareGrid::Draw() const
{
	setlinecolor(colorSets.m_ColorLine);
	setfillcolor(m_CurrentBGColor);
	fillrectangle(m_Position.AxisX, m_Position.AxisY, m_Position.AxisX + m_SideLength, m_Position.AxisY + m_SideLength);
	if (m_Num > 0 && m_Num < 10) {
		setbkmode(TRANSPARENT);
		settextcolor(colorSets.m_ColorText);
		settextstyle(40, 20, _T("ºÚÌå"));
		WCHAR tmp[2];
		swprintf_s(tmp, _T("%d"), m_Num);
		outtextxy(m_Position.AxisX + (m_SideLength - 20) / 2, m_Position.AxisY + (m_SideLength - 40) / 2, tmp);
	}	
}

void SquareGrid::Hover(const ExMessage& msg)
{
	if (
		msg.x > m_Position.AxisX && msg.x < (m_Position.AxisX + m_SideLength) &&
		msg.y > m_Position.AxisY && msg.y < (m_Position.AxisY + m_SideLength)
	) {
		m_CurrentBGColor = colorSets.m_ColorBGHover;
	} else {
		m_CurrentBGColor = colorSets.m_ColorBGDefault;
	}
}

void SquareGrid::Click(const ExMessage& msg)
{
	if (
		msg.x > m_Position.AxisX && msg.x < (m_Position.AxisX + m_SideLength) &&
		msg.y > m_Position.AxisY && msg.y < (m_Position.AxisY + m_SideLength) &&
		msg.message == WM_LBUTTONDOWN && Timer::Check(300, 0)
	) {
		AutoNum();
	}
}

void SquareGrid::AutoNum()
{
	if (m_Num == 0) return;
	if (m_Num < m_NumMax) {
		m_Num++;
	} else {
		m_Num = 1;
	}
}
