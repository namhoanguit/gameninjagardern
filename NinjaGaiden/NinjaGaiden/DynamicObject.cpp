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

// nam thêm 
// nam thêm
void DynamicObject::Stop()
{
	IsGoing = 0;
	m_bb.m_vx = 0;
}
void DynamicObject::Sit_SM()
{
	IsSitting = 1;
	IsFalling = 0;
	IsJumping = 0;
	IsGoing = 0;
}

void DynamicObject::Stand_SM()
{
	IsSitting = 0;
	IsFalling = 0;
	IsJumping = 0;
	IsGoing = 0;
}

void DynamicObject::Fall()
{
	IsFalling = 1;
	IsJumping = 0;
	IsSitting = 0;
	//EndHurt = 1;
}
void DynamicObject::Jump_SM()
{
	IsJumping = 1;
	IsFalling = 0;
	IsSitting = 0;
}
void DynamicObject::Go_SM()
{
	IsSitting = 0;
	IsFalling = 0;
	IsJumping = 0;
	IsGoing = 1;
}

