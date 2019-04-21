#include "fwWindows.h"
 

fwWindows::fwWindows(HINSTANCE hInstance, LPCTSTR windowsName, bool isWindowed,
	int width, int height, WinProcedurePointer WndProc,
	int backgroundColor)
{
	m_resolution.x = width;
	m_resolution.y = height;

	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));

	this->m_hInstance = hInstance;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.hInstance = this->m_hInstance;
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.hbrBackground = (HBRUSH)backgroundColor + 1;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.lpszClassName = windowsName;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);

	RegisterClassEx(&wcex);

	this->m_wndHandler = CreateWindow(windowsName, windowsName,
		isWindowed ? WS_OVERLAPPEDWINDOW :
		(WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE),
		CW_USEDEFAULT, CW_USEDEFAULT,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		NULL, NULL,
		m_hInstance, 0);

	if (!this->m_wndHandler) {
		return;
	}

	UpdateWindow(m_wndHandler);
	ShowWindow(m_wndHandler, SW_SHOW);
}



fwWindows::~fwWindows(void)
{
	if (m_d3dDevice != 0)		m_d3dDevice->Release();
	if (m_d3dObject != 0)		m_d3dObject->Release();
	if (m_spriteHandler != 0)	m_spriteHandler->Release();
}



D3DXVECTOR2 fwWindows::getResolution()
{
	return m_resolution;
}



LPD3DXSPRITE& fwWindows::getSpriteHandler()
{
	return m_spriteHandler;
}



HWND& fwWindows::getWindowHandler()
{
	return m_wndHandler;
}



LPDIRECT3D9& fwWindows::getD3DObject()
{
	return m_d3dObject;
}



LPDIRECT3DDEVICE9& fwWindows::getD3DDevice()
{
	return m_d3dDevice;
}



bool fwWindows::startRender()
{
	if (m_d3dDevice == 0) {
		return false;
	}
	else {
		m_d3dDevice->Clear(0, 0, D3DCLEAR_TARGET, 0xFF000000, 1.0f, 0);
		m_d3dDevice->BeginScene();
		m_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		return true;
	}
}



void fwWindows::stopRender()
{
	m_spriteHandler->End();
	m_d3dDevice->EndScene();
	m_d3dDevice->Present(0, 0, 0, 0);
}



bool fwWindows::StartingDevice(D3DXVECTOR2 screenResolution, bool isWindowed,
	int nBuffers, D3DSWAPEFFECT swapEffect)
{
	m_d3dObject = 0;
	m_d3dDevice = 0;

	if ((m_d3dObject = Direct3DCreate9(D3D_SDK_VERSION)) == 0) {
		return false;
	}

	D3DPRESENT_PARAMETERS theParameter;
	ZeroMemory(&theParameter, sizeof(theParameter));

	theParameter.Windowed = isWindowed;
	theParameter.BackBufferFormat = isWindowed ? D3DFMT_UNKNOWN : D3DFMT_X8R8G8B8;
	theParameter.BackBufferCount = nBuffers;
	theParameter.SwapEffect = swapEffect;
	theParameter.BackBufferWidth = (UINT)screenResolution.x;
	theParameter.BackBufferHeight = (UINT)screenResolution.y;
	theParameter.hDeviceWindow = this->m_wndHandler;

	HRESULT CreateDeviceResult = m_d3dObject->CreateDevice(
		D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_wndHandler,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &theParameter, &m_d3dDevice);

	if (FAILED(CreateDeviceResult)) {
		return false;
	}

	D3DXCreateSprite(m_d3dDevice, &m_spriteHandler);
	D3DXMatrixIdentity(&m_originalSpriteHandlerMatrix);
	//TextManager::createTextManager(m_d3dDevice, m_spriteHandler);
	return true;
}


void fwWindows::setWindowTitle(LPCTSTR newTitle)
{
	SetWindowText(m_wndHandler, newTitle);
}
