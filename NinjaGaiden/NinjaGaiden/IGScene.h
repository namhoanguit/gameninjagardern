#ifndef _IGSCENE_H_
#define _IGSCENE_H_
#include "fwconfig.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "MainObject.h"
#include "Hayabusa.h"
#include "fwCamera.h"
#include "Dog.h"

#include "BossBat.h"

#include "QuadTree.h"




#include "BanShee.h"
#include "SwordMan.h"
#include "Map.h"
#include "Runner.h"
#include "MachineGun.h"
#include "Rocket.h"

#include "Butterfly.h"

class IGScene
{
	Hayabusa* hayabusa;

	D3DXVECTOR3 m_posCamera;

	// Enemy
	Test * box;
	
	
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