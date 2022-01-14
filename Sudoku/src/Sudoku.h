#pragma once
#include <iostream>
#include <array>
#include "easyx.h"
#include "config.h"
#include "Timer.hpp"
#include "Widget/Win.h"
#include "Widget/SquareGrid.h"

class Sudoku
{
private:
	Win* m_WinControl;
	SquareGrid* m_DataMap[GRID_COUNT_SINGLE][GRID_COUNT_SINGLE];
public:
	Sudoku();
	~Sudoku();
	void Init();
	void Update();
	void Run();
};