#include <windows.h>

class Timer
{
public:
	static bool Check(unsigned int duration, unsigned short chanId)
	{

		static unsigned int start[TIMER_COUNT]{};
		if (chanId > 9) return false;
		unsigned int end = GetTickCount();
		if ((end - start[chanId]) > duration) {
			start[chanId] = end;
			return true;
		}
		return false;
	}
};