 
#ifndef __FW_WINDOWS_H__
#define __FW_WINDOWS_H__
#include <d3dx9.h>
#include "fwconfig.h"

typedef LRESULT(CALLBACK *WinProcedurePointer)(HWND, UINT, WPARAM, LPARAM);

class fwWindows
{
public:
	fwWindows(HINSTANCE hInstance, LPCTSTR windowsName,
		bool isWindowed,
		int width = SCREEN_WIDTH,
		int height = SCREEN_HEIGHT,
		WinProcedurePointer windowProcedure = 0,
		int backgroundColor = BLACK_BRUSH);

	~fwWindows(void);

	//Create Backbuffer
	bool StartingDevice(D3DXVECTOR2 screenResolution = D3DXVECTOR2(RESOLUTION_WIDTH, RESOLUTION_HEIGHT),
		bool isWindowed = TRUE, int nBuffers = 1,
		D3DSWAPEFFECT swapEffect = D3DSWAPEFFECT_COPY);

	D3DXVECTOR2			getResolution();
	LPD3DXSPRITE&		getSpriteHandler();
	HWND&				getWindowHandler();
	LPDIRECT3D9&		getD3DObject();
	LPDIRECT3DDEVICE9&	getD3DDevice();

	void				setWindowTitle(LPCTSTR newTitle);

	bool				startRender();
	void				stopRender();

private:

	HINSTANCE			m_hInstance;
	HWND				m_wndHandler;

	LPDIRECT3D9			m_d3dObject;
	LPDIRECT3DDEVICE9	m_d3dDevice;
	LPD3DXSPRITE		m_spriteHandler;

	D3DXVECTOR2			m_resolution;
	D3DXMATRIX			m_originalSpriteHandlerMatrix;
};

#endif
//__FW_WINDOWS_H__