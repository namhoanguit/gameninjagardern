#ifndef __FW_FPSCONTROLLER_H__
#define __FW_FPSCONTROLLER_H__

#include <d3d9.h>
#include <d3dx9.h>

class fwFPSController
{
private:
	DWORD m_BeginTime;
	DWORD m_CurTime;
	DWORD m_SmoothFPS;
	DWORD m_SleepTime;
	DWORD m_DeltaTime;
	DWORD m_FrameTime;

public:
	fwFPSController();
	virtual ~fwFPSController();

	void setFPS(DWORD _FPS);
	void beginTime();
	void endTimeSleep();
	DWORD getDeltatime();
	DWORD getCurrentFPS();
};

#endif 
// __FW_FPSCONTROLLER_H__