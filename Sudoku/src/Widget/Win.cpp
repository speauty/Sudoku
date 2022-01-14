#include "Win.h"

Win::Win(unsigned int width, unsigned int high, const std::string& consoleName)
	: m_Width(width), m_High(high), m_ConsoleName(consoleName)
{
	// 暂时不设置窗口名称
	// @todo m_ConsoleName
	initgraph(m_Width, m_High);
}

Win::~Win()
{
	closegraph();
}
