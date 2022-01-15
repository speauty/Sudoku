#include "Sudoku.h"
#include <vector>

void Sudoku::InitDataMap()
{
	for (unsigned int y = 0; y < GRID_COUNT_SINGLE; y++)
	{
		for (unsigned int x = 0; x < GRID_COUNT_SINGLE; x++)
		{
			m_DataMap[y][x] = { x + y * GRID_COUNT_SINGLE, {x * GRID_SIDE_LENGTH, y * GRID_SIDE_LENGTH}, SudokuTemplate[y][x], SudokuTemplate[y][x] != 0};
		}
	}
}

void Sudoku::Flush() const
{
	setbkcolor(COLOR_BG);
	cleardevice();
}

void Sudoku::SetGridTextStyle() const
{
	setbkmode(TRANSPARENT);
	settextcolor(COLOR_TEXT);
	settextstyle(40, 20, _T("黑体"));
}

void Sudoku::RenderWelcome() const
{
	if (m_State.process == ProcessFlags::PF_WELCOME) {
		settextstyle(40, 20, _T("黑体"));
		RECT textBlockRect = { 120, 90, 420, 150 };
		settextcolor(COLOR_TEXT_BLOCK);
		drawtext(_T("Sudoku-数独"), &textBlockRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		settextstyle(20, 10, _T("黑体"));
		textBlockRect = { 120, 180, 420, 240 };
		settextcolor(COLOR_TEXT_BLOCK);
		setlinecolor(COLOR_LINE_NORMAL);
		roundrect(225, 195, 315, 225, 20, 20);
		drawtext(_T("开始游戏"), &textBlockRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		

		textBlockRect = { 120, 240, 420, 280 };
		settextcolor(COLOR_TEXT_BLOCK);
		setlinecolor(COLOR_LINE_NORMAL);
		roundrect(225, 245, 315, 275, 20, 20);
		drawtext(_T("退出游戏"), &textBlockRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		settextstyle(40, 20, _T("黑体"));
	}
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

	if (cell.locked && m_State.process == ProcessFlags::PF_PLAY) {
		setfillcolor(COLOR_BG_GRID_LOCK);
	}
	fillrectangle(cell.position.AxisX, cell.position.AxisY, cell.position.AxisX + GRID_SIZE, cell.position.AxisY + GRID_SIZE);
}

void Sudoku::RenderGridVal(const SqureCell& cell) const
{
	if (m_State.process == ProcessFlags::PF_PLAY || m_State.process == ProcessFlags::PF_FINISH) {
		SetGridTextStyle();
		WCHAR tmp[2] = _T("");
		if (cell.val) swprintf_s(tmp, _T("%d"), cell.val);
		outtextxy(cell.position.AxisX + (GRID_SIZE - 20) / 2, cell.position.AxisY + (GRID_SIZE - 40) / 2, tmp);
	}
}

void Sudoku::RenderSpecialLine() const
{
	setlinecolor(COLOR_LINE_WEIGHT);
	line(3 * GRID_SIZE, 0, 3 * GRID_SIZE, GRID_COUNT_SINGLE * GRID_SIZE);
	line(6 * GRID_SIZE, 0, 6 * GRID_SIZE, GRID_COUNT_SINGLE * GRID_SIZE);
	line(0, 3 * GRID_SIZE, GRID_COUNT_SINGLE * GRID_SIZE, 3 * GRID_SIZE);
	line(0, 6 * GRID_SIZE, GRID_COUNT_SINGLE * GRID_SIZE, 6 * GRID_SIZE);
}

void Sudoku::RenderResultPanel()
{
	
	if (m_State.process == ProcessFlags::PF_FINISH) {
		RECT textBlockRect = { 120, 240, 420, 280 };
		settextcolor(COLOR_TEXT_BLOCK);
		if (m_State.flagSuccess) {
			drawtext(_T("成功"), &textBlockRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		} else {
			drawtext(_T("失败"), &textBlockRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
	}
}

Sudoku::Sudoku()
{
	/* 初始化窗口 */
	initgraph(GRID_SIZE * GRID_COUNT_SINGLE, GRID_SIZE * GRID_COUNT_SINGLE);
	m_State.process = ProcessFlags::PF_WELCOME;
	Init();
}

Sudoku::~Sudoku()
{
	closegraph();
}

void Sudoku::Checker()
{
	bool flag = true;
	if (m_State.process != ProcessFlags::PF_PLAY) return;
	static unsigned short log = 0;

	if (Timer::Check(3000, 1)) {
		for (unsigned int y = 0; y < GRID_COUNT_SINGLE; y++) {
			for (unsigned int x = 0; x < GRID_COUNT_SINGLE; x++) {
				if (!m_DataMap[y][x].val) flag = false;
			}
		}
		if (flag) {
			log++;
			if (log >= 3) m_State.process = ProcessFlags::PF_FINISH;
		}
	}
	

	for (unsigned int y = 0; y < GRID_COUNT_SINGLE; y++) {
		std::vector<bool> tmp = { false, false, false, false, false, false, false, false, false };
		for (unsigned int x = 0; x < GRID_COUNT_SINGLE; x++) {
			if (m_DataMap[y][x].val) tmp[m_DataMap[y][x].val - 1] = true;
		}
		std::vector<bool>::iterator tmpIt;
		tmpIt = std::unique(tmp.begin(), tmp.end());
		tmp.resize(std::distance(tmp.begin(), tmpIt));
		if (!(tmp.size() == 1 && tmp[0] == true)) return;
	}

	for (unsigned int y = 0; y < GRID_COUNT_SINGLE; y++) {
		std::vector<bool> tmp = { false, false, false, false, false, false, false, false, false };
		for (unsigned int x = 0; x < GRID_COUNT_SINGLE; x++) {
			if (m_DataMap[x][y].val) tmp[m_DataMap[x][y].val - 1] = true;
		}
		std::vector<bool>::iterator tmpIt;
		tmpIt = std::unique(tmp.begin(), tmp.end());
		tmp.resize(std::distance(tmp.begin(), tmpIt));
		if (!(tmp.size() == 1 && tmp[0] == true)) return;
	}

	for (unsigned int y = 0; y < GRID_COUNT_SINGLE; y++) {
		std::vector<bool> tmp = { false, false, false, false, false, false, false, false, false };
		for (unsigned int x = 0; x < GRID_COUNT_SINGLE; x++) {
			if (m_DataMap[x / 3 + (y / 3) * 3][x % 3 + (y % 3) * 3].val) tmp[m_DataMap[x / 3 + (y / 3) * 3][x % 3 + (y % 3) * 3].val - 1] = true;
		}
		std::vector<bool>::iterator tmpIt;
		tmpIt = std::unique(tmp.begin(), tmp.end());
		tmp.resize(std::distance(tmp.begin(), tmpIt));
		if (!(tmp.size() == 1 && tmp[0] == true)) return;
	}

	m_State.flagSuccess = 1;

	if (m_State.flagSuccess) {
		for (unsigned int y = 0; y < GRID_COUNT_SINGLE; y++)
		{
			for (unsigned int x = 0; x < GRID_COUNT_SINGLE; x++)
			{
				m_DataMap[y][x].locked = 1;
			}
		}
	}
}

void Sudoku::Init()
{
	InitDataMap();
	SetGridTextStyle();
}

void Sudoku::Draw()
{
	Flush();
	RenderGrid();
	RenderSpecialLine();
	RenderWelcome();
}

void Sudoku::UpdateGridVal(SqureCell& cell)
{
	if (cell.locked) return;
	if (cell.val < GRID_NUM_MAX) {
		cell.val++;
	}
	else {
		cell.val = 0;
	}
}

void Sudoku::EventMouseListener(const ExMessage& msg)
{
	if (m_State.process == ProcessFlags::PF_WELCOME) {
		if ( msg.x > 225 && msg.x < 315 && msg.y > 195 && msg.y < 225 ) {
			setlinecolor(COLOR_TEXT_BLOCK);
			roundrect(225, 195, 315, 225, 20, 20);
			if (msg.message == WM_LBUTTONDOWN) {
				m_State.process = ProcessFlags::PF_PLAY;
			}
		} else if ( msg.x > 225 && msg.x < 315 && msg.y > 245 && msg.y < 275 ) {
			setlinecolor(COLOR_TEXT_BLOCK);
			roundrect(225, 245, 315, 275, 20, 20);
			if (msg.message == WM_LBUTTONDOWN) {
				m_State.process = ProcessFlags::PF_EXIT;
			}
		}
	} else if (m_State.process == ProcessFlags::PF_PLAY) {
		unsigned int mayIdxX = msg.x / GRID_SIDE_LENGTH;
		unsigned int mayIdxY = msg.y / GRID_SIDE_LENGTH;
		if (mayIdxX < GRID_COUNT_SINGLE && mayIdxY < GRID_COUNT_SINGLE) {
			RenderGrid(mayIdxX, mayIdxY, COLOR_BG_GRID_HOVER);
			RenderSpecialLine();
			if (msg.message == WM_LBUTTONDOWN && Timer::Check(TIMER_GRID_CLICK_DURATION, TIMER_GRID_CLICK_CHAN)) {
				UpdateGridVal(m_DataMap[mayIdxY][mayIdxX]);
			}
		}
	}
}

void Sudoku::Run()
{
	Checker();
	ExMessage msg;
	BeginBatchDraw();
	while (m_State.process != ProcessFlags::PF_EXIT) {
		Draw();
		peekmessage(&msg, EM_MOUSE);
		EventMouseListener(msg);
		RenderResultPanel();
		if (m_State.process == ProcessFlags::PF_FINISH && Timer::Check(3000, 5)) {
			m_State.process = ProcessFlags::PF_WELCOME;
		}
		FlushBatchDraw();
		Checker();
		
	}
	EndBatchDraw();
}
