
#include "fwloopGame.h"

//STANDARD LIBRARY
#include <tchar.h>
#include <string>
#include <stdlib.h>

//GAME PARAMETERS
#include "fwconfig.h"
#include "fwmacro.h"
#include "fwFPSController.h"


//DEVICE GAME
#include "fwKeyboard.h"

#include "fwTexture.h"
#include "fwCamera.h"

//#include "Camera.h"
//#include "utils.h"
//#include "Hidden_Bricks.h"
//#include "Play_Map_CutsMan.h"
//#include "Enemies\BigEye.h"

#include "Resources.h"


using namespace std;


fwloopGame::fwloopGame(HINSTANCE hInstance)
{
	//Init device to provide for game
	m_displayWindow = new fwWindows(hInstance, WINDOWS_NAME, true, SCREEN_WIDTH, SCREEN_HEIGHT, fwloopGame::WndProc);
	m_displayWindow->StartingDevice();

	fwKEYBOARD_CONTROLLER_INSTANCE->init(hInstance, m_displayWindow->getWindowHandler());
	
	fwTexture::initHandler(m_displayWindow->getSpriteHandler());
	srand(time(NULL));

	//Init component in game
	fwloopGame::init();
}




fwloopGame::~fwloopGame(void)
{
	SAFE_RELEASE(m_displayWindow);
}



LRESULT CALLBACK fwloopGame::WndProc(HWND WindowsHandle, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(WindowsHandle, Message, wParam, lParam);
}





void fwloopGame::runGame()
{
	MSG Message;
	ZeroMemory(&Message, sizeof(Message));

	m_fpscontroller = new fwFPSController();
	m_fpscontroller->setFPS(FPS);

	//---------------------------------------LOOP GAME---------------------------------------
	while (Message.message != WM_QUIT)
	{
		m_fpscontroller->beginTime();
		static string window_name = WINDOWS_NAME;
		static string windows_name_fps;
		windows_name_fps = window_name + " - FPS: " + to_string((m_fpscontroller->getCurrentFPS()));
		m_displayWindow->setWindowTitle(windows_name_fps.c_str());
		fwTexture::setPositioncConvertMatrix(fwCAMERA_INSTANCE->gettransformCoordinates());
		//fwBoundingBox::setPositioncConvertMatrix(fwCAMERA_INSTANCE->gettransformCoordinates());

		update(m_fpscontroller->getDeltatime());

		fwCAMERA_INSTANCE->update(m_fpscontroller->getCurrentFPS());

		render();

		if (PeekMessage(&Message, 0, 0U, 0U, PM_REMOVE)) {
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		m_fpscontroller->endTimeSleep();
	}
	delete m_fpscontroller;
	release();
	//---------------------------------------------------------------------------------------
}


void fwloopGame::release()
{

	fwTexture::releaseHandler();
	//GameState::release();
}




//------------------------------------------------------------------------------------------
// Init object in game to run.
void fwloopGame::init()
{
	RES_INSTANCE->init();
	//CODE HERE
	scene = new IGScene;
}

void fwloopGame::update(DWORD deltaTime)
{
	fwKEYBOARD_CONTROLLER_INSTANCE->update();
	//CODE HERE
	scene->update(deltaTime);
}

void fwloopGame::render()
{
	if (m_displayWindow->startRender())
	{
		//CODE HERE
		scene->draw();

		m_displayWindow->stopRender();
	}
}
//------------------------------------------------------------------------------------------