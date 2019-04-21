#ifndef _Test_H_
#define _Test_H_

#include "StaticObject.h"


//Terrain: Platform(1) and Spine(0)
class Test :public StaticObject
{


public:
	Test();
	~Test();
	Test(BoundingBox, IDObject = idPLATFORM);
	void draw();

};
#endif