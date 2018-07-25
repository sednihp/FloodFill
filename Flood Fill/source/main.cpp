#include "Engine.h"
#include <time.h>
#include "Util.h"

int main(int, char**)
{
	srand(static_cast<unsigned>(time(0)));

	Engine engine;

	while(engine.isRunning())
	{
		engine.run();
	}

    return 0;
}