#ifndef __FW_LOOP_GAME_H__
#define __FW_LOOP_GAME_H__

#include <time.h>

#include "fwWindows.h"
#include "fwmacro.h"
#include "fwKeyboard.h"
#include "fwFPSController.h"
#include "IGScene.h"



class fwloopGame
{
	fwFPSController *m_fpscontroller;

	IGScene* scene;

public:
	fwloopGame(HINSTANCE hInstance);
	~fwloopGame(void);
	void runGame();

private:
	static LRESULT CALLBACK WndProc(HWND WindowsHandle, UINT Message, WPARAM wParam, LPARAM lParam);

	//StageManager *stage_manager;

	void update(DWORD deltaTime);

	//Render object in game.
	void render();

	// Init object in game to run.
	void init();
	// Release device 
	void release();

private:
	fwWindows*	m_displayWindow;


};

#endif
//__FW_LOOP_GAME_H__