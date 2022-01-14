#pragma once
#include <iostream>
#include "easyx.h"

/**
 * 控件-窗口类
 **/
class Win
{
private:
	unsigned int m_Width;		/* 窗口宽度 */
	unsigned int m_High;		/* 窗口高度 */
	std::string  m_ConsoleName;	/* 窗口名称 */

public:
	Win(unsigned int width, unsigned int high, const std::string& consoleName);
	~Win();
};