#include "Resources.h"
#define BACKGROUND "res\\images\\map1.png"
#define PATH_SIMON "res\\images\\hayabusa\\all.bmp"
#include "Hayabusa.h"

Resources *Resources::m_instance = nullptr;
fwAnimation **Resources::m_animationSimon = nullptr;
fwTexture *Resources::m_txtSimon = nullptr;


fwSprite **Resources::m_spriteSimon = new fwSprite*[_STATE::eCount];

Resources::Resources()
{

	m_animationSimon = new fwAnimation*[_STATE::eCount];
	m_txtSimon = new fwTexture(PATH_SIMON, D3DCOLOR_XRGB(0, 0, 128));

	m_spriteSimon[_STATE::eSTAND] = new fwSprite(m_txtSimon, D3DXVECTOR3(0, 0, 0),1, 1, 17, 32);
	m_spriteSimon[_STATE::eSIT] = new fwSprite(m_txtSimon, D3DXVECTOR3(0, 47, 0), 1, 1, 31.5, 24);
	m_spriteSimon[_STATE::eRUN] = new fwSprite(m_txtSimon, D3DXVECTOR3(336, 0, 0), 3, 3, 27, 31);



	m_spriteSimon[_STATE::eJUMP] = new fwSprite(m_txtSimon, D3DXVECTOR3(135, 47, 0), 4, 4, 25, 22);

	// nam thêm 

	m_spriteSimon[_STATE::eAttacking] = new fwSprite(m_txtSimon, D3DXVECTOR3(60, 0, 0), 2, 2,45, 29);
	m_spriteSimon[_STATE::eSitAttacking] = new fwSprite(m_txtSimon, D3DXVECTOR3(51,47, 0), 2, 2, 42, 23);

	m_animationSimon[_STATE::eSTAND] = new fwAnimation(m_spriteSimon[_STATE::eSTAND], 200);
	m_animationSimon[_STATE::eSIT] = new fwAnimation(m_spriteSimon[_STATE::eSIT], 200);
	m_animationSimon[_STATE::eRUN] = new fwAnimation(m_spriteSimon[_STATE::eRUN], 100);
	m_animationSimon[_STATE::eJUMP] = new fwAnimation(m_spriteSimon[_STATE::eJUMP], 500);

	// nam thêm
	m_animationSimon[_STATE::eAttacking] = new fwAnimation(m_spriteSimon[_STATE::eAttacking], 500);
	m_animationSimon[_STATE::eSitAttacking] = new fwAnimation(m_spriteSimon[_STATE::eSitAttacking], 500);
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