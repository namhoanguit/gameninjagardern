#ifndef __DYNAMIC_OBJECT_H__
#define __DYNAMIC_OBJECT_H__

#include "StaticObject.h"



D3DXVECTOR2 DIRECTION(bool isRight);


class DynamicObject :public StaticObject
{
	
public:

	DynamicObject();
	~DynamicObject(){}

	float getVX();
	float getVY();
	void setVelocity(float vx, float vy);

	virtual void update(DWORD deltatime) = 0;
	
};

#endif