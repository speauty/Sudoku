#pragma once
#include <iostream>
#include "easyx.h"

/**
 * �ؼ�-������
 **/
class Win
{
private:
	unsigned int m_Width;		/* ���ڿ�� */
	unsigned int m_High;		/* ���ڸ߶� */
	std::string  m_ConsoleName;	/* �������� */

public:
	Win(unsigned int width, unsigned int high, const std::string& consoleName);
	~Win();
};