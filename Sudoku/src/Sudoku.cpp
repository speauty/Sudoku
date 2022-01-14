#include "Sudoku.h"

Sudoku::Sudoku()
{
	Init();
}

Sudoku::~Sudoku()
{
	delete m_WinControl;
	for (unsigned short y = 0; y < GRID_COUNT_SINGLE; y++)
	{
		for (unsigned short x = 0; x < GRID_COUNT_SINGLE; x++)
		{
			delete m_DataMap[y][x];
		}
	}
}

void Sudoku::Init()
{
	/* ³õÊ¼»¯´°¿Ú */
	m_WinControl = new Win(GRID_SIZE * GRID_COUNT_SINGLE, GRID_SIZE * GRID_COUNT_SINGLE, GAME_NAME);
	//colorSets.m_ColorLineWeight
	for (unsigned short y = 0; y < GRID_COUNT_SINGLE; y++)
	{
		for (unsigned short x = 0; x < GRID_COUNT_SINGLE; x++)
		{
			Position tmp = { x * GRID_SIZE, y * GRID_SIZE };
			m_DataMap[y][x] = new SquareGrid(x + y * GRID_COUNT_SINGLE, tmp, GRID_SIZE, 0, GRID_NUM_MAX );
			m_DataMap[y][x]->Draw();
		}
	}
}

void Sudoku::Update()
{

}

void Sudoku::Run()
{
	ExMessage msg;
	BeginBatchDraw();
	while (1) {
		peekmessage(&msg, EM_MOUSE);
		for (unsigned short y = 0; y < GRID_COUNT_SINGLE; y++)
		{
			for (unsigned short x = 0; x < GRID_COUNT_SINGLE; x++)
			{
				m_DataMap[y][x]->Hover(msg);
				m_DataMap[y][x]->Click(msg);
				m_DataMap[y][x]->Draw();
			}
		}
		setlinecolor(colorSets.m_ColorLineWeight);
		line(3 * GRID_SIZE, 0, 3 * GRID_SIZE, GRID_COUNT_SINGLE * GRID_SIZE);
		line(6 * GRID_SIZE, 0, 6 * GRID_SIZE, GRID_COUNT_SINGLE * GRID_SIZE);
		line(0, 3 * GRID_SIZE, GRID_COUNT_SINGLE * GRID_SIZE, 3 * GRID_SIZE);
		line(0, 6 * GRID_SIZE, GRID_COUNT_SINGLE * GRID_SIZE, 6 * GRID_SIZE);
		FlushBatchDraw();
	}
	EndBatchDraw();
}
