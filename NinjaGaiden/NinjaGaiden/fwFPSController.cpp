#include "fwFPSController.h"
//#include "utils.h"

float clamp(float _variable, float _left, float _right)
{
	if (_left <= _right)
	{
		if (_variable < _left)
		{
			_variable = _left;
		}
		if (_variable > _right)
		{
			_variable = _right;
		}
	}
	return _variable;
}

fwFPSController::fwFPSController()
{
}


fwFPSController::~fwFPSController()
{
}


void fwFPSController::setFPS(DWORD _FPS)
{
	m_SmoothFPS = _FPS;
	m_DeltaTime = m_FrameTime = 1000 / _FPS;
}

void fwFPSController::beginTime()
{
	m_BeginTime = GetTickCount();
}

void fwFPSController::endTimeSleep()
{
	m_CurTime = GetTickCount();
	m_DeltaTime = 1000 / m_SmoothFPS;
	m_SleepTime = DWORD(clamp(m_FrameTime - ((m_CurTime - m_BeginTime)) % 1000, 0, m_FrameTime));
	if (m_SleepTime == m_FrameTime)return;
	m_DeltaTime = m_FrameTime - m_SleepTime;
	Sleep(m_SleepTime);
}

DWORD fwFPSController::getDeltatime()
{
	return m_DeltaTime;
}

DWORD fwFPSController::getCurrentFPS()
{
	return 1000 / m_DeltaTime;
}