#pragma once
#ifndef _MAP_H_
#define _MAP_H_

#include <stdio.h>
#include <conio.h>
#include "fwSprite.h"
#include "fwTexture.h"
#include "fwCamera.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "fwAnimation.h"
using namespace std;
class Map
{
private:

	int RowMatrix = 0;
	int ColumnMatrix = 160;
	int TileMap[13][160];
	
	//int State = 1; //-1: Menu ; 0: Intro, 1: Màn 1, 2: Màn 2, 3: Màn 3

	/////////////////////////////////
	//Bổ sung thêm code(tiền)
	int ScreenColumn;
	int ScreenRow;
	int row, column;
	float x, y;
	D3DXVECTOR3 m_Pos;
public:
	fwTexture* m_texture;
	fwSprite* m_sprite;
	fwAnimation* m_animation;
	Map(int State);
	~Map();
	void ReadMap(char * filename, int State);
	void LoadMap(int State);
	void DrawMap(fwCamera *camera, int State);
	void DrawMap2(fwCamera *camera, int State);
	//int getState() { return State; };
	//void setState(int a) { State = a; };
	////////////////////////////////
	/////////Source code bổ sung hàm drawmap2 khi mà va chạm cổng ở màn 1 chuyển sang màn 2
	void DrawMap2(LPDIRECT3DDEVICE9 d3ddv, fwCamera* camera);
};

#endif
