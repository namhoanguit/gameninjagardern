#include "IGScene.h"

IGScene::IGScene()
{
	//m_mainobj = new MainObject();
	//box = new Test(BoundingBox(0, 10, 500, 5));



	

		//// enemy
	banshee = new BanShee();
	dog = new  Dog();
	swordman = new SwordMan();
	runner = new Runner();
	rocket = new Rocket();
	gun = new MachineGun();
		//bat = new Bat();
	//death = new Death();

	//// Boss
	//boss_bat = new BossBat();
	//// item
	bird = new Bird();	// con chim
	butterfly = new Butterfly();	// con buom




	InitMap();







}

IGScene::~IGScene()
{
	delete hayabusa; box; ball; left;
	delete dog,bat,death,boss_bat;
	delete food,bigheart,smallheart;


	// - ninja gaiden
	delete banshee,swordman,gun,rocket,runner;

	// item
	delete butterfly, bird;

}

void IGScene::update(DWORD deltatime)
{
	//m_mainobj->update(deltatime);

	//bat->update(deltatime);*/
	//death->update(deltatime);
	////boss_bat->update(deltatime);





	//// enemy
	////food->update(deltatime);
	////bigheart->update(deltatime);


	//// Test
	//m_sweepAABB.checkCollisionBySweeepAABB(m_mainobj->getBoundingBox(), box->getBoundingBox(), deltatime);
	//m_mainobj->updateCollide(m_sweepAABB, deltatime);



	//// Nam thêm 
	//// 1 - con chó
	////m_sweepAABB.checkCollisionBySweeepAABB(dog->getBoundingBox(), box->getBoundingBox(), deltatime);
	////dog->updateCollide(m_sweepAABB, deltatime);



	////// 2 - con dơi

	////m_sweepAABB.checkCollisionBySweeepAABB(bat->getBoundingBox(), box->getBoundingBox(), deltatime);
	////bat->updateCollide(m_sweepAABB, deltatime);


	////// 3 - con ma

	////m_sweepAABB.checkCollisionBySweeepAABB(death->getBoundingBox(9,5), m_mainobj->getBoundingBox(3,15), deltatime);
	////death->updateCollide(m_sweepAABB, deltatime);
	////// Con boss

	////m_sweepAABB.checkCollisionBySweeepAABB(boss_bat->getBoundingBox(), box->getBoundingBox(), deltatime);
	////boss_bat->updateCollide(m_sweepAABB, deltatime);


	//////updateScene(deltatime);

	////// Food
	////m_sweepAABB.checkCollisionBySweeepAABB(food->getBoundingBox(), box->getBoundingBox(), deltatime);
	////food->updateCollide(m_sweepAABB, deltatime);

	////m_sweepAABB.checkCollisionBySweeepAABB(bigheart->getBoundingBox(), box->getBoundingBox(), deltatime);
	////bigheart->updateCollide(m_sweepAABB, deltatime);

	////m_sweepAABB.checkCollisionBySweeepAABB(smallheart->getBoundingBox(), box->getBoundingBox(), deltatime);
	////smallheart->updateCollide(m_sweepAABB, deltatime);


	
	//left->update(deltatime);



	// enemy

	banshee->update(deltatime);
	dog->update(deltatime);

	runner->update(deltatime);
	rocket->update(deltatime);
	gun->update(deltatime);
	swordman->update(deltatime);




	// item

	butterfly->update(deltatime);
	bird->update(deltatime);
	ball->update(deltatime);
	updateQT();

	updateKeyBoard(deltatime);

	updateCollide(deltatime);
	
	updateScene(deltatime);
}
void IGScene::updateKeyBoard(DWORD deltatime)
{

	
	hayabusa->update(deltatime);
	
	ball->update(deltatime);

	 
	if (fwGET_KEY(DIK_V) == KEY_PRESS)
		m_visibleScene = m_visibleScene ? false : true;
}
void IGScene::updateCollide(DWORD deltatime)
{
	int i;
	SweepAABB nearestCol, tempCol;

	for (i = 0; i < m_main.size(); i++)
	{
		tempCol.checkCollisionBySweeepAABB(hayabusa, m_main.at(i), deltatime);

		if (tempCol.m_colDirection == NO)continue;

		if ((tempCol.m_colDirection != NO) &&
			tempCol.m_colTime < nearestCol.m_colTime)

		{
			nearestCol = tempCol;
		}

	}


	hayabusa->updateCollide(nearestCol, deltatime);
}
void IGScene::draw()
{
	map->DrawMap(fwCAMERA_INSTANCE, 1);
	
	if (m_visibleScene)
	{
		
		//m_sceneMap->drawFrame(m_posCamera);
		hayabusa->draw();
	}
	else
	{
		for (int i = 0; i < m_main.size(); i++)
			m_main.at(i)->draw();
		
		hayabusa->draw();
		hayabusa->drawBoundingBox(COLOR_RED);
	}
	ball->draw();



	// nam thêm
	banshee->draw();
	dog->draw();
	swordman->draw();
	runner->draw();
	rocket->draw();
	gun->draw();


	//item
	bird->draw();
	butterfly->draw();

	ball->drawBoundingBox(COLOR_RED);
}



void IGScene::updateScene(DWORD deltatime)
{
	if (hayabusa->GetCam() == true)
		m_posCamera.x += hayabusa->getVX()*deltatime / 1000;
	//m_posCamera.y += m_mainobj->getVY()*deltatime / 1000;
	fwCAMERA_INSTANCE->setPossition(m_posCamera);
	m_sceneMap->setPosInTexture(D3DXVECTOR3(m_posCamera.x,
		m_sizeQT - m_posCamera.y - RESOLUTION_HEIGHT, 0));
}

void IGScene::InitMap()
{
	hayabusa = new Hayabusa();
	ball = new Ball();

	
	
	//
	m_visibleScene = true;

	map = new Map(1);

	QuadTree::m_vectorEntitiesEnemy.clear();
	QuadTree::m_vectorEntitiesTerrain.clear();
	QuadTree::m_maxlevelEnemy = QuadTree::m_maxlevelTerrain = 0;

	m_qt= new QuadTree(eTypeQTTerrain);
	m_qt->readfile(PATH_OBJECT1);
	m_sizeQT = m_qt->getSizeNodeTree();


	
	m_sceneMap = new fwSprite(new fwTexture(PATH_MAP));
	m_sceneMap->setSizeFrame(RESOLUTION_WIDTH, RESOLUTION_HEIGHT);
	m_sceneMap->setPosInTexture(D3DXVECTOR3(0, 0, 0));


	m_posCamera.x =0;
	m_posCamera.y = -200;
	fwCAMERA_INSTANCE->setPossition(m_posCamera);
	if (hayabusa->GetCam() == true)
		hayabusa->setPosition(D3DXVECTOR3(fwCAMERA_INSTANCE->getPossition().x + RESOLUTION_WIDTH / 2
		, fwCAMERA_INSTANCE->getPossition().y + RESOLUTION_HEIGHT / 2, 0));

}

void IGScene::updateQT()
{
	m_main.clear();


	m_qt->extractIntoVectorEntitiesByRegion(fwCAMERA_INSTANCE->getBoundingBox(),
		&m_main);
}