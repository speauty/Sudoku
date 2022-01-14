#include "Sudoku.h"

int main()
{
	Sudoku sudo;
	sudo.Run();
	/*GridColorSets colorSets = { GRID_BGCOLOR_DEFAULT, GRID_BGCOLOR_HOVER, GRID_BGCOLOR_CLICKED, GRID_COLOR_TEXT };
	Position testPosition = {120, 120};
	Win winControl(GRID_SIZE * GRID_COUNT_SINGLE, GRID_SIZE * GRID_COUNT_SINGLE, GAME_NAME);
	SquareGrid grid(testPosition, GRID_SIZE, 1, GRID_NUM_MAX, colorSets);
	ExMessage msg;
	BeginBatchDraw();
	while (1) {
		peekmessage(&msg, EM_MOUSE);
		grid.Draw();
		grid.Hover(msg);
		if (Timer::Check(150, 0)) {
			grid.Click(msg);
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
	
	std::cin.get();*/
}