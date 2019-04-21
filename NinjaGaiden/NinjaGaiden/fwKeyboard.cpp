#include "fwKeyboard.h"
#include "fwmacro.h"

fwKeyboard *fwKeyboard::m_instance = nullptr;

// -----------------------------------------------
// Name: Keyboard:Keyboard()
// Desc: Create an interface to get the keyboard status.
// -----------------------------------------------
fwKeyboard::fwKeyboard()
{

}

void fwKeyboard::init(HINSTANCE hInstance, HWND windowHandler)
{
	m_inputDevice = 0;
	m_inputDevice_Keyboard = 0;
	m_hInstance = hInstance;
	m_windowHandler = windowHandler;
	if (!createKeyboard())
	{
		return;
	}
}

fwKeyboard *fwKeyboard::getInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new fwKeyboard();
	}

	return m_instance;
}

// -----------------------------------------------
// Name: Keyboard:~Keyboard()
// Desc: Release the interface after use (close game).
// -----------------------------------------------
fwKeyboard::~fwKeyboard()
{
	if (m_inputDevice_Keyboard != 0)
	{
		m_inputDevice_Keyboard->Unacquire();
		m_inputDevice_Keyboard->Release();
		m_inputDevice_Keyboard = 0;
	}

	if (m_inputDevice != 0)
	{
		m_inputDevice->Release();
		m_inputDevice = 0;
	}

	SAFE_DELETE_POINTER(m_instance);
}


// -----------------------------------------------
// Name: Keyboard:createKeyboard()
// Desc: Create keyboard interface.
// -----------------------------------------------
bool fwKeyboard::createKeyboard()
{
	HRESULT result = DI_OK;

	result = result | DirectInput8Create(m_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_inputDevice, 0);
	result = result | m_inputDevice->CreateDevice(GUID_SysKeyboard, &m_inputDevice_Keyboard, 0);

	result = result | m_inputDevice_Keyboard->SetDataFormat(&c_dfDIKeyboard);
	result = result | m_inputDevice_Keyboard->SetCooperativeLevel(m_windowHandler, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	result = result | m_inputDevice_Keyboard->Acquire();

	if (result != DI_OK)
		return false;
	return true;
}


// -----------------------------------------------
// Name: Keyboard:update()
// Desc: Store the old keyboard status then get the new one.
// -----------------------------------------------
void fwKeyboard::update()
{
	memcpy(m_keyboardStatusPrevious, m_keyboardStatus, sizeof(m_keyboardStatus));

	HRESULT result;
	int i = sizeof(m_keyboardStatus);
	result = m_inputDevice_Keyboard->GetDeviceState(sizeof(m_keyboardStatus), (LPVOID)&m_keyboardStatus);

	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_inputDevice_Keyboard->Acquire();
		}
	}
}


// -----------------------------------------------
// Name: Keyboard:getKeyStatus()
// Desc: Check if the key is DOWN, UP, just PRESS or just RELEASE.
// -----------------------------------------------
KeyStatus fwKeyboard::getKeyStatus(int key)
{
	if (CHECK_IF_STATUS_IS_DOWN(m_keyboardStatus[key])) {
		if (CHECK_IF_STATUS_IS_DOWN(m_keyboardStatusPrevious[key]))
			return KeyStatus::KEY_DOWN;
		else
			return KeyStatus::KEY_PRESS;
	}
	else {
		if (CHECK_IF_STATUS_IS_DOWN(m_keyboardStatusPrevious[key]))
			return KeyStatus::KEY_RELEASE;
		else
			return KeyStatus::KEY_UP;
	}
}