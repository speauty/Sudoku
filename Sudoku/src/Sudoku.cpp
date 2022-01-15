#include "Sudoku.h"

void Sudoku::InitDataMap()
{
	for (unsigned int y = 0; y < GRID_COUNT_SINGLE; y++)
	{
		for (unsigned int x = 0; x < GRID_COUNT_SINGLE; x++)
		{
			m_DataMap[y][x] = { x + y * GRID_COUNT_SINGLE, {x * GRID_SIDE_LENGTH, y * GRID_SIDE_LENGTH}, 0 };
		}
	}
}

void Sudoku::Flush() const
{
	setbkcolor(COLOR_BG);
	cleardevice();
}

void Sudoku::RenderGrid() const
{
	for (unsigned int y = 0; y < GRID_COUNT_SINGLE; y++)
	{
		for (unsigned int x = 0; x < GRID_COUNT_SINGLE; x++)
		{
			RenderGridRect(m_DataMap[y][x], COLOR_BG_GRID_DEFAULT);
			RenderGridVal(m_DataMap[y][x]);
		}
	}
}

void Sudoku::RenderGrid(unsigned char idxX, unsigned char idxY, unsigned int bgColor) const
{
	if (idxX < GRID_COUNT_SINGLE && idxY < GRID_COUNT_SINGLE) {
		RenderGridRect(m_DataMap[idxY][idxX], bgColor);
		RenderGridVal(m_DataMap[idxY][idxX]);
	}
}

void Sudoku::RenderGridRect(const SqureCell& cell, unsigned int bgColor) const
{
	setlinecolor(COLOR_LINE_NORMAL);
	setfillcolor(bgColor);
	fillrectangle(cell.position.AxisX, cell.position.AxisY, cell.position.AxisX + GRID_SIZE, cell.position.AxisY + GRID_SIZE);
}

void Sudoku::RenderGridVal(const SqureCell& cell) const
{
	if (!cell.val) return;
	setbkmode(TRANSPARENT);
	settextcolor(COLOR_TEXT);
	settextstyle(40, 20, _T("黑体"));
	WCHAR tmp[2];
	swprintf_s(tmp, _T("%d"), cell.val);
	outtextxy(cell.position.AxisX + (GRID_SIZE - 20) / 2, cell.position.AxisY + (GRID_SIZE - 40) / 2, tmp);

}

void Sudoku::RenderSpecialLine() const
{
	setlinecolor(COLOR_LINE_WEIGHT);
	line(3 * GRID_SIZE, 0, 3 * GRID_SIZE, GRID_COUNT_SINGLE * GRID_SIZE);
	line(6 * GRID_SIZE, 0, 6 * GRID_SIZE, GRID_COUNT_SINGLE * GRID_SIZE);
	line(0, 3 * GRID_SIZE, GRID_COUNT_SINGLE * GRID_SIZE, 3 * GRID_SIZE);
	line(0, 6 * GRID_SIZE, GRID_COUNT_SINGLE * GRID_SIZE, 6 * GRID_SIZE);
}

Sudoku::Sudoku()
{
	/* 初始化窗口 */
	initgraph(GRID_SIZE * GRID_COUNT_SINGLE, GRID_SIZE * GRID_COUNT_SINGLE, EW_SHOWCONSOLE);
	m_State.process = ProcessFlags::PF_WELCOME;
	Init();
}

Sudoku::~Sudoku()
{
	closegraph();
}

void Sudoku::Init()
{
	InitDataMap();
}

void Sudoku::Draw()
{
	Flush();
	RenderGrid();
	RenderSpecialLine();
}

void Sudoku::UpdateGridVal(SqureCell& cell)
{
	if (cell.val == 0) return;
	if (cell.val < GRID_NUM_MAX) {
		cell.val++;
	}
	else {
		cell.val = 1;
	}
}

void Sudoku::Update()
{

}

void Sudoku::EventMouseListener(ExMessage msg)
{
	unsigned int mayIdxX = msg.x / GRID_SIDE_LENGTH;
	unsigned int mayIdxY = msg.y / GRID_SIDE_LENGTH;
	if (mayIdxX < GRID_COUNT_SINGLE && mayIdxY < GRID_COUNT_SINGLE) {
		RenderGrid(mayIdxX, mayIdxY, COLOR_BG_GRID_HOVER);
		if (msg.message == WM_LBUTTONDOWN && Timer::Check(TIMER_GRID_CLICK_DURATION, TIMER_GRID_CLICK_CHAN)) {
			std::cout << "X: " << mayIdxX << " Y: " << mayIdxY << " 左键点击" << std::endl;
			UpdateGridVal(m_DataMap[mayIdxY][mayIdxX]);
		}
	}
	
}

void Sudoku::Run()
{
	ExMessage msg;
	BeginBatchDraw();
	while (1) {
		Draw();
		peekmessage(&msg, EM_MOUSE);
		EventMouseListener(msg);
		FlushBatchDraw();
	}
	EndBatchDraw();
}
