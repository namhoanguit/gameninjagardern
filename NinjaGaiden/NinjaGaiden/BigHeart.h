

#include "DynamicObject.h"
#include "fwAnimation.h"
#include "fwKeyboard.h"
#include "Collision.h"


class BigHeart : public DynamicObject
{
	fwAnimation* m_animation;
	fwTexture* m_texture;
	fwSprite* m_sprite;

public:
	BigHeart();
	~BigHeart();

	void update(DWORD deltatime);

	void updateCollide(SweepAABB, DWORD deltatime = 16);


	void draw();
};





