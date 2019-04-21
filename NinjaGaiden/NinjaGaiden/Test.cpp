#include "Test.h"


Test::Test(){}
Test::~Test(){}

Test::Test(BoundingBox bb, IDObject idobj)
{
	m_bb = bb;
	m_Id = idobj;
	m_visibleBB = true;

}
void Test::draw()
{
	m_visibleBB ? BOUNDINGBOX_DRAW(m_bb, COLOR_RED) : false;
}