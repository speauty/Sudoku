#pragma once

#include <iostream>
#include <easyx.h>
#include "config.h"
#include "Timer.hpp"

enum class ProcessFlags
{
	PF_EMPTY = 0, PF_WELCOME = 1, PF_PLAY = 2, PF_FINISH = 3, PF_EXIT = 4
};

struct State
{
	ProcessFlags process = ProcessFlags::PF_EMPTY;
};

class Sudoku
{
private:
	State m_State;
	SqureCell m_DataMap[GRID_COUNT_SINGLE][GRID_COUNT_SINGLE];

private:
	void InitDataMap();
	void Flush() const;
	void SetGridTextStyle() const;
	void RenderWelcome() const;
	void RenderGrid() const;
	void RenderGrid(unsigned char idxX, unsigned char idxY, unsigned int bgColor) const;
	void RenderGridRect(const SqureCell& cell, unsigned int bgColor) const;
	void RenderGridVal(const SqureCell& cell) const;
	void RenderSpecialLine() const;

	void Init();
	void Draw();
	void UpdateGridVal(SqureCell& cell);
	void EventMouseListener(const ExMessage& msg);

public:
	Sudoku();
	~Sudoku();
	void Run();
};