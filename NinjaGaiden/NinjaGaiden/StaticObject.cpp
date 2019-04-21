#include "StaticObject.h"
#include "Collision.h"

void StaticObject::setPosition(D3DXVECTOR3 pos){ m_Pos = pos; }
D3DXVECTOR3 StaticObject::getPosistion(){ return m_Pos; }

void StaticObject::setIdObject(IDObject id){ m_Id = id; }
IDObject StaticObject::getIdObject(){ return m_Id; }

BoundingBox StaticObject::getBoundingBox(){ return m_bb; }
void StaticObject::setBoundingBox(BoundingBox bb){ m_bb = bb; }

StaticObject::StaticObject()
{
	m_Pos = D3DXVECTOR3(0, 0, 0);
	m_Id = IDObject::UNKNOW;
	m_bb.m_pos = m_Pos;
	m_bb.m_vx = m_bb.m_vy = m_bb.m_height = m_bb.m_width = 0;

}


void StaticObject::setVisibleBoundingBox(bool visible) { m_visibleBB = visible; }
bool StaticObject::getVisibleBoundingBox(){ return m_visibleBB; }

void StaticObject::drawBoundingBox(D3DCOLOR color) { BOUNDINGBOX_DRAW(m_bb, color); }

bool StaticObject::compareValueObj(StaticObject& obj)
{
	return (m_Id == obj.m_Id) && (m_bb.compareValue(obj.m_bb));
}

BoundingBox StaticObject::getBoundingBox(float boxx, float boxy)
{ 
	m_bb.m_width = m_bb.m_width - boxx;
	m_bb.m_height = m_bb.m_height - boxy;
	return m_bb; 
}