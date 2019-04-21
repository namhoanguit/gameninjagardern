
#include "StaticObject.h"
#include "Collision.h"


class EnergyWater : public StaticObject
{
	fwTexture* m_texture;
	fwSprite* m_sprite;
	StaticObject *obj_static;

public:
	EnergyWater();
	~EnergyWater();

	void updateCollide(SweepAABB, DWORD deltatime = 16);
	void draw();
};






