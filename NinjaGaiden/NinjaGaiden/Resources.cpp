#include "Resources.h"
#define BACKGROUND "res\\images\\map1.png"
#define PATH_SIMON "res\\images\\ninja.png"
#include "Simon.h"

Resources *Resources::m_instance = nullptr;
fwAnimation **Resources::m_animationSimon = nullptr;
fwTexture *Resources::m_txtSimon = nullptr;


fwSprite **Resources::m_spriteSimon = new fwSprite*[SIMON_STATE::eCount];

Resources::Resources()
{

	m_animationSimon = new fwAnimation*[SIMON_STATE::eCount];
	m_txtSimon = new fwTexture(PATH_SIMON, D3DCOLOR_XRGB(0, 0, 128));

	m_spriteSimon[SIMON_STATE::eSTAND] = new fwSprite(m_txtSimon, D3DXVECTOR3(0, 0, 0),1, 1, 25, 36);
	m_spriteSimon[SIMON_STATE::eSIT] = new fwSprite(m_txtSimon, D3DXVECTOR3(0, 0, 0), 3, 3, 25, 36);
	m_spriteSimon[SIMON_STATE::eRUN] = new fwSprite(m_txtSimon, D3DXVECTOR3(0, 0, 0), 3, 3, 25, 36);
	m_spriteSimon[SIMON_STATE::eJUMP] = new fwSprite(m_txtSimon, D3DXVECTOR3(0, 0, 0), 3, 3, 25, 36);

	m_animationSimon[SIMON_STATE::eSTAND] = new fwAnimation(m_spriteSimon[SIMON_STATE::eSTAND], 200);
	m_animationSimon[SIMON_STATE::eSIT] = new fwAnimation(m_spriteSimon[SIMON_STATE::eSIT], 200);
	m_animationSimon[SIMON_STATE::eRUN] = new fwAnimation(m_spriteSimon[SIMON_STATE::eRUN], 200);
	m_animationSimon[SIMON_STATE::eJUMP] = new fwAnimation(m_spriteSimon[SIMON_STATE::eJUMP], 200);
}

Resources::~Resources()
{
	release();
}

Resources* Resources::getInstance()
{
	if (m_instance == nullptr)m_instance = new Resources();
	return m_instance;
}

void Resources::init()
{

	//INIT TEXTUREs AND SPRITEs


}

void Resources::release()
{
	delete m_txtSimon;
	delete[] m_spriteSimon;
	delete[] m_animationSimon;

	m_txtSimon = nullptr;
	m_spriteSimon = nullptr;
	m_animationSimon = nullptr;
	SAFE_DELETE_POINTER(m_instance);



#pragma region SPRITE
	//PLAYER??
#pragma endregion


#pragma region ANIMATION
	//PLAYER??
#pragma endregion







}




#pragma endregion TEXTURE_MAP
const char* PATH_TEXTURE_MPFNWP1 = "res//images//map//MegaManX4-FinalWeapon-Area1.png";
#pragma endregion


#pragma region QUADTREE_FILE
const char* PATH_TERRAIN_FNWP1 = "..\\Space Partitioning\\output\\terrain\\finalweapon1\\finalweapon1.txt";


#pragma endregion