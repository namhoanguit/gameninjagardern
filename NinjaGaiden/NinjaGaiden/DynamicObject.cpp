#include "DynamicObject.h"


D3DXVECTOR2 DIRECTION(bool isRight)
{
	if (isRight)return SCALE_NO;
	else return SCALE_FLIP_X;
}

float DynamicObject::getVX()
{
	return m_bb.m_vx;
}

float DynamicObject::getVY()
{
	return m_bb.m_vy;
}

void DynamicObject::setVelocity(float vx, float vy)
{
	m_bb.m_vx = vx;
	m_bb.m_vy = vy;
}

DynamicObject::DynamicObject()
{
	
}
