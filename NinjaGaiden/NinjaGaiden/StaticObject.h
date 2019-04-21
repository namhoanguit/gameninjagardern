#ifndef __STATIC_OBJECT_H__
#define __STATIC_OBJECT_H__

#include <d3d9.h>
#include <d3dx9.h>

#include "Resources.h"
#include "Collision.h"
#include "fwTexture.h"

enum IDObject
{
	//PLAYER
	//BOSSS
	//ENEMY
	//ITEM
	//PLATFORM
	idSPINE = 0,
	idPLATFORM,
	idPLAYER,
	idENEMY,
	idBOSS,
	COUNT,
	NONE,
	UNKNOW
};

class StaticObject
{
protected:
	D3DXVECTOR3 m_Pos, m_posDrawCenter;
	IDObject m_Id;
	BoundingBox m_bb;


	bool m_visibleBB;

public:
	StaticObject();
	~StaticObject(){}


	virtual void draw() = 0;

	void setPosition(D3DXVECTOR3);
	D3DXVECTOR3 getPosistion();

	void setIdObject(IDObject);
	IDObject getIdObject();

	void setBoundingBox(BoundingBox bb);
	BoundingBox getBoundingBox();

	void setVisibleBoundingBox(bool);
	bool getVisibleBoundingBox();

	void drawBoundingBox(D3DCOLOR);

	bool compareValueObj(StaticObject&);

	BoundingBox  getBoundingBox(float boxx, float boxy);


};
#endif