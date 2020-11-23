// --------------------------------------------------------
// Main : starts application logic
// --------------------------------------------------------
//#include <vld.h>
#include "Logic/GameApp.h"

int main(int argc, char** argv[])
{
	// game logic start
	GameApp app;
	if (!app.Init())
	{
		// APP init failed, code 1
		return 1;
	}
	app.Run();
	app.Shutdown();

	return 0;
}


