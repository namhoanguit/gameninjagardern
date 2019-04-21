

#include "DynamicObject.h"
#include "fwAnimation.h"
#include "fwKeyboard.h"
#include "Collision.h"


class SmallHeart : public DynamicObject
{
	fwAnimation* m_animation;
	fwTexture* m_texture;
	fwSprite* m_sprite;

public:
	SmallHeart();
	~SmallHeart();

	void update(DWORD deltatime);

	void updateCollide(SweepAABB, DWORD deltatime = 16);


	void draw();
};






