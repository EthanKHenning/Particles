#include "Engine.h"

int main()
{
    srand(time(nullptr));
	// Declare an instance of Engine
	Engine engine;
	// Start the engine
	engine.run();
	// Quit in the usual way when the engine is stopped
	return 0;
}