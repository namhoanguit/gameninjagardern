#ifndef _MAIN_OBJ_H_
#define _MAIN_OBJ_H_

#include "DynamicObject.h"
#include "fwAnimation.h"
#include "fwKeyboard.h"
#include "Collision.h"



class MainObject : public DynamicObject
{
	
	
public:
	MainObject();
	~MainObject();

	void update(DWORD deltatime);

	void updateKeyBoard(DWORD deltatime);
	void updateCollide(SweepAABB, DWORD deltatime = 16);


	void draw();

	
};


#endif





