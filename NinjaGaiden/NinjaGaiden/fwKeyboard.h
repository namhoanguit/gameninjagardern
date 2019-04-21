#ifndef __FW_KEYBOARD_H__
#define __FW_KEYBOARD_H__

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <Windows.h>
#include <dinput.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "fwconfig.h"

#define CHECK_IF_STATUS_IS_DOWN(status) (status & 0x80)

enum KeyStatus
{
	KEY_DOWN = 0,
	KEY_PRESS,
	KEY_RELEASE,
	KEY_UP,
	NUM_OF_KEY_STATUS
};

class fwKeyboard
{
public:
	void update();
	KeyStatus getKeyStatus(int key);

	static fwKeyboard *getInstance();

	void init(HINSTANCE hInstance, HWND windowHandler);

private:
	bool createKeyboard();
	fwKeyboard();
	~fwKeyboard();

private:
	HWND					m_windowHandler;
	HINSTANCE				m_hInstance;
	IDirectInput8*			m_inputDevice;
	IDirectInputDevice8*	m_inputDevice_Keyboard;

	BYTE					m_keyboardStatus[256];
	BYTE					m_keyboardStatusPrevious[256];

	static fwKeyboard	*m_instance;

};

#define fwKEYBOARD_CONTROLLER_INSTANCE		fwKeyboard::getInstance()
#define fwGET_KEY(A) fwKEYBOARD_CONTROLLER_INSTANCE->getKeyStatus(A)
#endif