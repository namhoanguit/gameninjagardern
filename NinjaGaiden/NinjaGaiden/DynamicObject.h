#ifndef __DYNAMIC_OBJECT_H__
#define __DYNAMIC_OBJECT_H__

#include "StaticObject.h"



D3DXVECTOR2 DIRECTION(bool isRight);


class DynamicObject :public StaticObject
{
	
	// nam thêm
protected:
	int IsGoing;		// Đang di chuyển = 1; Đứng yên = 0;
	int IsAttacking;
	int IsStopping;
	int IsJumping;
	int IsSitting;
	int IsFalling;
	int IsHurting;

public:

	// nam thêm
	
		void Jump_SM();
		void Sit_SM();
		void Go_SM();
		void Stand_SM();
		void Fall();
		void Attacking();
		void Sit_Attacking();
		void Stop();
		void MoveLeft();
		void MoveRigh();



	DynamicObject();
	~DynamicObject(){}

	float getVX();
	float getVY();
	void setVelocity(float vx, float vy);

	virtual void update(DWORD deltatime) = 0;
	
};

#endif