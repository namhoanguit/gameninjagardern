#ifndef _IGSCENE_H_
#define _IGSCENE_H_
#include "fwconfig.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "MainObject.h"
#include "Hayabusa.h"
#include "fwCamera.h"
#include "Dog.h"
#include "Bat.h"
#include "Death.h"
#include "BossBat.h"
#include "Food.h"
#include "SmallHeart.h"
#include "BigHeart.h"
#include "BigFire.h"
#include "SmallFire.h"
#include "Creese.h"
#include "EnergyWater.h"
#include "Whip.h"
#include "Door1.h"
#include "Door2.h"
#include "Gate1.h"
#include "Gate2.h"
#include "Brick.h"
#include "QuadTree.h"
#include "Ball.h"
#include "Left.h"
#include "Right.h"



#include "BanShee.h"
#include "SwordMan.h"
#include "Map.h"
#include "Runner.h"
#include "MachineGun.h"
#include "Rocket.h"

#include "Butterfly.h"
#include "Bird.h"
class IGScene
{
	Hayabusa* hayabusa;

	D3DXVECTOR3 m_posCamera;

	// Enemy
	Test * box;
	
	Bat *bat;
	Death * death;
	Left * left;
	
	Ball * ball;
	// Enemy - ninja garden

	BanShee * banshee;
	Dog *dog;
	SwordMan * swordman;
	Runner * runner;
	Rocket * rocket;
	MachineGun * gun;

	// Boss
	BossBat* boss_bat;

	// Item
	// nam thêm
	Butterfly *butterfly;
	Bird *bird;


	Creese * cresse; // item dao gam
	Whip * whip; // item doi da
	EnergyWater * energywater;  // item nuoc tang luc
	Food* food;
	BigHeart * bigheart;
	SmallHeart * smallheart;
	

	// Ground
	BigFire *bigFire;

	SmallFire * smallfire;
	Brick *brick;
	Door1 * door1;
	Door2 * door2;
	Gate1 * gate1;
	Gate2 * gate2;
	
	Map* map;

	SweepAABB m_sweepAABB;

	fwSprite* m_sceneMap;
	int m_sizeQT;
	bool m_visibleScene;
	QuadTree* m_qt;
	vector<StaticObject*> m_main;
public:
	IGScene();
	~IGScene();
	void InitMap();
	void updateQT();
	void update(DWORD deltatime);
	void updateScene(DWORD deltatime);
	void updateKeyBoard(DWORD);
	void updateCollide(DWORD deltatime);
	void draw();

};
#endif