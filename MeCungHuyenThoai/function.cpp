#include "function.h"

std::random_device rd;
std::mt19937 gen(rd());

int ABS(int a)
{
	return (a >= 0) ? a : -a;
}

int random(int start, int end)
{

	if (end < start)
	{
		int tmp = end;
		end = start;
		start = tmp;
	}
    std::uniform_int_distribution<> distrib(start, end);

   return distrib(gen);
}