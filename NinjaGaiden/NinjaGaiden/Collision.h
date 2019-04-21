#ifndef __COLLISION_H__
#define __COLLISION_H__

#include <cmath>
#include <algorithm>
#include <limits>


#include "BoundingBox.h"

class StaticObject;

enum IDObject;

enum eColDirection
{
	NO,
	LEFT,
	RIGHT,
	TOP,
	BOT
};

struct SweepAABB
{
	//---------------ATTRIBUTE---------------------------------------
	eColDirection m_colDirection;
	float m_colTime; // range 0 to 1.

	//---------------FUNCTION----------------------------------------
	SweepAABB();

	SweepAABB(eColDirection colDirection, float colTime);


	static BoundingBox GetSweptBroadPhaseBox(BoundingBox box1);
	static bool CheckAABB(BoundingBox box1, BoundingBox box2);
	static eColDirection AABB(BoundingBox box1, BoundingBox box2);
	static float algorithmSweepAABB(BoundingBox box1, BoundingBox box2, float& normalx, float& normaly);
	SweepAABB checkCollisionBySweeepAABB(BoundingBox box1, BoundingBox box2, DWORD deltatime = 16);
	SweepAABB checkCollisionBySweeepAABB(StaticObject* box1, StaticObject* box2, DWORD deltatime = 16);

	SweepAABB checkCollisionBySweeepAABB_new(StaticObject*  box1, StaticObject*  box2, DWORD deltatime, float x, float y);
	SweepAABB checkCollisionBySweeepAABB_new(BoundingBox box1, BoundingBox box2, DWORD deltatime, float x, float y);
	//---------------------------------------------------------------
};


#endif



