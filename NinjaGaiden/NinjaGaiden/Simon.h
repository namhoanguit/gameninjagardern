#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include "MainObject.h"


enum SIMON_STATE
{
	eSTAND=0,
	eSIT,
	eRUN,
	eJUMP,
	eCount
};


//Terrain: Platform(1) and Spine(0)
class Simon :public DynamicObject
{
	fwAnimation* m_animation;
	fwTexture* m_texture;
	fwSprite* m_sprite;
	bool isleft;

public:
	Simon();
	~Simon();
	Simon(BoundingBox, IDObject = idPLATFORM);
	void draw();
	void Jump_SM();
	void Sit_SM();
	void Go_SM();
	void Stand_SM();
	bool GetCam();
	void update(DWORD deltatime);
	void updateCollide(SweepAABB, DWORD deltatime = 16);
};
#endif