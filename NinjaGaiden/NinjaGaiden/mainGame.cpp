#include <windows.h>
#include "fwloopGame.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	fwloopGame* CastleVania = new fwloopGame(hInstance);
	CastleVania->runGame();
	SAFE_RELEASE(CastleVania);

	return 0;
}

