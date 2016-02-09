#include <iostream>
#include "IAsyncBTAlg.h"

int main()
{
	CAsyncBacktackAlg test("nQueens.lua", 4, 4);
	test.StartAlgorhythm();
	system("pause");
}