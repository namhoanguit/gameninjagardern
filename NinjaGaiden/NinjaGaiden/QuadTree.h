#ifndef _QUAD_TREE_H_
#define _QUAD_TREE_H_
#include "StaticObject.h"
#include "Test.h"
#include <vector>
using namespace std;

enum eTypeQuadTree
{
	eTypeQTTerrain = 0,
	eTypeQTEnemy,
	eTypeQTItem,
	eTypeQuadTreeCount
};

class QuadTree
{
private:
	int m_currlevel;
	eTypeQuadTree m_typeQuadTree;

	BoundingBox m_region;
	vector<StaticObject*> m_vectorEntitiesCurrNodeQT;
	QuadTree** m_nodeQT;

public:
	static vector<StaticObject*> m_vectorEntitiesTerrain;
	static vector<StaticObject*> m_vectorEntitiesEnemy;


	static int m_maxlevelTerrain;
	static int m_maxlevelEnemy;

	void insertValuetoNode(QuadTree*);
	bool isContain(StaticObject&);
	bool isContain(BoundingBox&);


	int compareRegion(BoundingBox&);

	QuadTree** getNodeQT(){ return m_nodeQT; }

	void split();

	void clear();

	void readfile(const char* filename, eTypeQuadTree typequadtree = eTypeQTTerrain);
	void createQuadTreeByMaxLevel();

	QuadTree(eTypeQuadTree);
	QuadTree(int level, BoundingBox region, eTypeQuadTree typequadtree);//
	~QuadTree();


	int* getPointermCurrLevel(){ return &m_currlevel; }
	BoundingBox* getPointerRegion(){ return &m_region; }

	vector<StaticObject*>* getPointerVectorCurrNode(){ return &m_vectorEntitiesCurrNodeQT; }
	StaticObject* checkEntityInStaticVectorQT(StaticObject*);
	StaticObject* createEntityByID(IDObject&, BoundingBox&);

	QuadTree* findNodeQuadTreeByNode(QuadTree*);

	void extractIntoVectorEntitiesByRegion(BoundingBox&,
		vector<StaticObject*>* m_vectorEntitiesCollide);

	int getSizeNodeTree();

	void saveFile(char* filename);
	void Override(FILE* file);
};

#endif