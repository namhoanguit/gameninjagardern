#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#include "fwAnimation.h"
#include "fwconfig.h"

#pragma region TEXTURE_MAP

extern const char* PATH_TEXTURE_MPFNWP1;

#pragma endregion

#pragma region QUADTREE_FILE
extern const char* PATH_TERRAIN_FNWP1;


#pragma endregion



#pragma region SOUND_PLAYER
#define PATH_SOUND_PLX_READY (tchar*)"res//sounds/player/x/PL00_U_00012.wav"


#pragma endregion



class Resources
{
private:
	Resources();
	~Resources();

	static Resources* m_instance;
public:
	static Resources* getInstance();
	void init();
	void release();

	//LIST TEXTUREs AND SPRITEs FOR GAME
#pragma region TEXTURE


	static fwAnimation** m_animationSimon;
	static fwSprite** m_spriteSimon;
	static fwTexture* m_txtSimon;


#pragma endregion


};

#define RES_INSTANCE Resources::getInstance()


#endif