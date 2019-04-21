#include "QuadTree.h"

vector<StaticObject*> QuadTree::m_vectorEntitiesTerrain;
vector<StaticObject*> QuadTree::m_vectorEntitiesEnemy;



int QuadTree::m_maxlevelTerrain = 0;
int QuadTree::m_maxlevelEnemy = 0;

QuadTree::QuadTree(eTypeQuadTree typequadtree)
{
	m_typeQuadTree = typequadtree;
	m_currlevel = 0;
	m_vectorEntitiesCurrNodeQT.clear();
	m_vectorEntitiesTerrain.clear();
	m_vectorEntitiesEnemy.clear();
	m_nodeQT = nullptr;
	//m_region???
}

void QuadTree::clear()
{
	if (m_nodeQT) //m_nodeQT != nullptr
	{
		for (int i = 0; i < 4; i++)
		{
			m_nodeQT[i]->clear();
			delete m_nodeQT[i];
			m_nodeQT[i] = nullptr;
		}

		delete[] m_nodeQT;
		m_nodeQT = nullptr;
	}
	m_vectorEntitiesCurrNodeQT.clear();
}

QuadTree::~QuadTree()
{
	this->clear();
}

QuadTree::QuadTree(int level, BoundingBox region, eTypeQuadTree typequadtree)
{
	m_typeQuadTree = typequadtree;
	m_currlevel = level;
	m_region = region;
	m_vectorEntitiesCurrNodeQT.clear();
	m_nodeQT = nullptr;
}

void QuadTree::split()
{
	if (!m_nodeQT) // m_nodeQT == nullptr
	{
		m_nodeQT = new QuadTree*[4];

		float width = m_region.m_width / 2;
		float height = m_region.m_height / 2;

		m_nodeQT[0] = new QuadTree(m_currlevel + 1, BoundingBox(m_region.m_pos.x, m_region.m_pos.y, width, height), m_typeQuadTree);

		m_nodeQT[1] = new QuadTree(m_currlevel + 1, BoundingBox(m_region.m_pos.x + width, m_region.m_pos.y, width, height), m_typeQuadTree);

		m_nodeQT[2] = new QuadTree(m_currlevel + 1, BoundingBox(m_region.m_pos.x, m_region.m_pos.y + height, width, height), m_typeQuadTree);

		m_nodeQT[3] = new QuadTree(m_currlevel + 1, BoundingBox(m_region.m_pos.x + width, m_region.m_pos.y + height, width, height), m_typeQuadTree);

	}

}

void QuadTree::createQuadTreeByMaxLevel()
{
	if (!m_nodeQT && m_currlevel < m_maxlevelTerrain)
	{
		split();
		for (int i = 0; i < 4; i++)
			m_nodeQT[i][0].createQuadTreeByMaxLevel();
	}
}


void QuadTree::readfile(const char* filename, eTypeQuadTree typequadtree)
{
	FILE* file = fopen(filename, "r");
	m_typeQuadTree = typequadtree;
	this;
	if (!file)// file == nullptr
	{
		cout << "Cann't open file" << endl;
		return;
	}

	//Read data Region map into original QuadTree
	m_typeQuadTree == eTypeQTTerrain ?
		fscanf(file, "QT %f %f %f %f %d\n", &m_region.m_pos.x,
		&m_region.m_pos.y, &m_region.m_width, &m_region.m_height, &m_maxlevelTerrain) : false;

	m_typeQuadTree == eTypeQTEnemy ?
		fscanf(file, "QT %d %d %d %d %d\n", &m_region.m_pos.x,
		&m_region.m_pos.y, &m_region.m_width, &m_region.m_height, &m_maxlevelTerrain) : false;

	createQuadTreeByMaxLevel();

	//Size vector of curr node in quadTree.
	int sizenode = 0;

	//Declare Node.
	QuadTree*  node;

	//Init entity.
	StaticObject* entity = nullptr;
	IDObject idEntity;
	BoundingBox bbEntity;
	int level;

	//fscanf(file, "\n");
	//Read everyNode (level,corrdinate,width,height)
	while (fscanf(file, "QT %d %f %f %f %f %d\n",
		&level, &bbEntity.m_pos.x, &bbEntity.m_pos.y,
		&bbEntity.m_width, &bbEntity.m_height, &sizenode) != EOF)
		//while (fscanf(file, "QT %d %f %f %f %f %d\n",
		//	node->getPointermCurrLevel(),
		//	&(node->getPointerRegion()->m_pos.x),
		//	&(node->getPointerRegion()->m_pos.y),
		//	&(node->getPointerRegion()->m_width),
		//	&(node->getPointerRegion()->m_height), &sizenode) != EOF)
	{
		//lv = (node->getPointerRegion()->m_height);
		//Init Node
		this;
		node = new QuadTree(level, bbEntity, m_typeQuadTree);

		for (int i = 0; i < sizenode; i++)
		{

			//Read entity and save them into vector of currNode.
			fscanf(file, "%d %f %f %f %f\n",
				&idEntity, &bbEntity.m_pos.x, &bbEntity.m_pos.y,
				&bbEntity.m_width, &bbEntity.m_height);

			//Create StaticObj Object.
			entity = createEntityByID(idEntity, bbEntity);

			//check Static VectorQT contain entity, 
			//if not to add entity into that vector.
			entity = checkEntityInStaticVectorQT(entity);

			//Add pointer of entity into cur vector node.
			node->getPointerVectorCurrNode()->push_back(entity);
			idEntity = NONE;
			m_vectorEntitiesTerrain;
		}
		insertValuetoNode(node);
		delete node;
		node = nullptr;
		fscanf(file, "\n");
	}

	m_vectorEntitiesTerrain;

	//Close File
	fclose(file);

}

//Name:createEntityByID
//Des:Init Entity - pointer StaticObject by ID
StaticObject* QuadTree::createEntityByID(IDObject& id, BoundingBox& bb)
{
	switch (id)
	{
	case idSPINE:
		return new Test(bb, id);
		break;
	case idPLATFORM:
		return new Test(bb, id);
		break;
	case idENEMY:
		break;
	case idBOSS:
		break;
	default:
		break;
	}
}



//Name: checkEntityInStaticVectorQT
//Des: check Static VectorQT contain entity, 
//	   if not to add entity into that vector.
StaticObject* QuadTree::checkEntityInStaticVectorQT(StaticObject* entity)
{
	if (m_typeQuadTree == eTypeQTTerrain)
	{
		for (int i = 0; i < m_vectorEntitiesTerrain.size(); i++)
		{
			if (m_vectorEntitiesTerrain.at(i)->compareValueObj(*entity))
			{
				delete entity;
				entity = m_vectorEntitiesTerrain.at(i);
				return entity;
			}
		}
		m_vectorEntitiesTerrain.push_back(entity);
		return entity;
	}
	if (m_typeQuadTree == eTypeQTEnemy)
	{
		for (int i = 0; i < m_vectorEntitiesEnemy.size(); i++)
		{
			if (m_vectorEntitiesEnemy.at(i)->compareValueObj(*entity))
			{
				delete entity;
				entity = m_vectorEntitiesEnemy.at(i);
				return entity;
			}
		}
		m_vectorEntitiesEnemy.push_back(entity);
		return entity;
	}
}

bool QuadTree::isContain(StaticObject& entity)
{
	return !(entity.getBoundingBox().m_pos.x + entity.getBoundingBox().m_width < m_region.m_pos.x ||
		entity.getBoundingBox().m_pos.y + entity.getBoundingBox().m_height < m_region.m_pos.y ||
		entity.getBoundingBox().m_pos.x > m_region.m_pos.x + m_region.m_width ||
		entity.getBoundingBox().m_pos.y > m_region.m_pos.y + m_region.m_height);
}

bool QuadTree::isContain(BoundingBox& bb)
{
	return !(bb.m_pos.x + bb.m_width < m_region.m_pos.x ||
		bb.m_pos.y + bb.m_height < m_region.m_pos.y ||
		bb.m_pos.x > m_region.m_pos.x + m_region.m_width ||
		bb.m_pos.y > m_region.m_pos.y + m_region.m_height);
}

//Name: compareRegion
//Des: compare region of quadtree with ref-bb
//Res: -1:contained 
//		0:bb 's curr region node of quadtree 
//		1:Not contained.
int QuadTree::compareRegion(BoundingBox& bb)
{
	if (m_region.compareValue(bb))return 0;

	if (m_region.m_pos.x <= bb.m_pos.x && m_region.m_pos.y <= bb.m_pos.y &&
		((m_region.m_pos.x + m_region.m_width) >= (bb.m_pos.x + bb.m_width)) &&
		((m_region.m_pos.y + m_region.m_height) >= (bb.m_pos.y + bb.m_height)))
		return -1;


	return 1;
}

//Name:findNodeQuadTreeByNode
//Des:Find level and region node in QuadTree
QuadTree* QuadTree::findNodeQuadTreeByNode(QuadTree* nodeIn)
{
	if (m_nodeQT)
	{
		for (int i = 0; (i < 4); i++)
		{
			switch (m_nodeQT[i][0].compareRegion(nodeIn->m_region))
			{
			case -1:
				return m_nodeQT[i][0].findNodeQuadTreeByNode(nodeIn);
				break;
			case 0:
				return &m_nodeQT[i][0];
				break;
			case 1:
				continue;
				break;
			}
		}
	}
}

//Name:insertNode
//Des:Add Object into curr vector node of QuadTree
void QuadTree::insertValuetoNode(QuadTree* node)
{
	QuadTree* nodeOfQT = nullptr;
	nodeOfQT = findNodeQuadTreeByNode(node);
	*nodeOfQT;
	nodeOfQT->clear();
	//nodeOfQT = node;
	for (auto i = 0; i < node->getPointerVectorCurrNode()->size(); i++)
		nodeOfQT->getPointerVectorCurrNode()->push_back(
		node->getPointerVectorCurrNode()->at(i));
}

//Name:extractIntoVectorEntitiesByRegion
//Des: return Vector staticObj may be collide.
void QuadTree::extractIntoVectorEntitiesByRegion(BoundingBox& region,
	vector<StaticObject*>* m_vectorEntitiesCollide)
{
	if (m_nodeQT)
	{
		if (m_nodeQT[0]->isContain(region))
			m_nodeQT[0]->extractIntoVectorEntitiesByRegion(region, m_vectorEntitiesCollide);
		if (m_nodeQT[1]->isContain(region))
			m_nodeQT[1]->extractIntoVectorEntitiesByRegion(region, m_vectorEntitiesCollide);
		if (m_nodeQT[2]->isContain(region))
			m_nodeQT[2]->extractIntoVectorEntitiesByRegion(region, m_vectorEntitiesCollide);
		if (m_nodeQT[3]->isContain(region))
			m_nodeQT[3]->extractIntoVectorEntitiesByRegion(region, m_vectorEntitiesCollide);

		return;
	}
	//m_vectorEntitiesTerrain;
	int j;
	//push back entities in current region - leaf node into m_vectorEntitiesCollide
	if (this->isContain(region))
	{
		for (auto i = 0; i < m_vectorEntitiesCurrNodeQT.size(); i++)
		{
			//m_vectorEntitiesCollide.push_back();
			for (j = 0; j < m_vectorEntitiesCollide->size(); j++)
			{
				if (m_vectorEntitiesCurrNodeQT.at(i)->compareValueObj(
					*(m_vectorEntitiesCollide->at(j))))break;
			}

			if (j < m_vectorEntitiesCollide->size())continue;

			if (j == m_vectorEntitiesCollide->size())
				m_vectorEntitiesCollide->push_back(m_vectorEntitiesCurrNodeQT.at(i));
		}
	}
}

void QuadTree::Override(FILE* file)
{
	if (!m_vectorEntitiesCurrNodeQT.empty())
	{
		fprintf(file, "QT %d %d %d %d %d %d\n",
			(int)m_currlevel,
			(int)m_region.m_pos.x, (int)m_region.m_pos.y,
			(int)m_region.m_width, (int)m_region.m_height,
			(int)m_vectorEntitiesCurrNodeQT.size());

		for (int i = 0; i < m_vectorEntitiesCurrNodeQT.size(); i++)
		{
			fprintf(file, "%d %d %d %d %d\n",
				(int)(m_vectorEntitiesCurrNodeQT.at(i)->getIdObject()),
				(int)m_vectorEntitiesCurrNodeQT.at(i)->getBoundingBox().m_pos.x,
				(int)m_vectorEntitiesCurrNodeQT.at(i)->getBoundingBox().m_pos.y,
				(int)m_vectorEntitiesCurrNodeQT.at(i)->getBoundingBox().m_width,
				(int)m_vectorEntitiesCurrNodeQT.at(i)->getBoundingBox().m_height);

		}
		fprintf(file, "\n");
	}

	if (m_nodeQT != nullptr)
	{
		for (int i = 0; i < 4; i++)
		{
			m_nodeQT[i]->Override(file);
		}
	}
}

void QuadTree::saveFile(char* filename)
{
	/*string path = PATH_OUTPUT;
	path.append(filename);
	strcpy(filename, path.c_str());*/

	FILE* file = fopen(filename, "w+");

	//Write first node of Quadtreee.
	fprintf(file, "QT %d %d %d %d %d\n\n",
		(int)m_region.m_pos.x, (int)m_region.m_pos.y,
		(int)m_region.m_width, (int)m_region.m_height,
		(int)m_maxlevelTerrain);


	BoundingBox* Bound = new BoundingBox();


	Override(file);

	fclose(file);
}

int QuadTree::getSizeNodeTree()
{
	return m_region.m_width;
}