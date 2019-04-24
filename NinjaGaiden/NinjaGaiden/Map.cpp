#include "Map.h"
#include "fwconfig.h"

#define PATH_MAINMENU "./res/images/ctb.PNG"
#define PATH_INTRO "./res/images/mainmenu1.png"
#define PATH_MAP1 "res\\images\\ctb.PNG"
#define PATH_MAP2 "res\\images\\map\\stage2.png"

Map::Map(int State)
{
	m_Pos = D3DXVECTOR3(0, 0, 0);
	LoadMap(State);

}

Map::~Map()
{

}
void Map::ReadMap(char * filename, int State)
{
	try
	{
		ifstream file;
		file.open(filename, ios::in);
		int dem = -1;
		if (file.fail())
			dem = -2;
		
		while (!file.eof())
		{
			for (int j = 0; j < ColumnMatrix; j++)
			{
				file >> dem;
				TileMap[RowMatrix][j] = dem;
			}
			RowMatrix++;
		}
		int a = RowMatrix;
		file.close();
	}
	catch (exception e)
	{
		
	}

}
void Map::LoadMap(int State)
{
	 
		ReadMap("res/images/stage1.txt", State);
		m_texture = new fwTexture(PATH_MAP1, D3DCOLOR_XRGB(255, 0, 255));
		m_sprite = new fwSprite(m_texture, D3DXVECTOR3(0, 0, 0), 16, 144, 32, 32);
		m_animation = new fwAnimation(m_sprite, 200);// 500 là thời gian chuyển đổi giữa 2 frame liên tiếp, càng lớn càng chậm
	 
	ScreenColumn = (SCREEN_WIDTH) / m_animation->getFrameWidth() + 2;
	ScreenRow = (SCREEN_HEIGHT) / m_animation->getFrameHeight();
	//RESOLUTION_WIDTH = (m_sprite->getFrameHeight)*(ColumnMatrix*(State > 0) + (State == 0));//dùng ở hàm SceneMain.cpp
	//G_MapHeight = (GTTile->FrameHeight)*(RowMatrix*(State > 0) + (State == 0));
	//GSTile = new fwSprite();
}
void Map::DrawMap(fwCamera* camera, int State)
{
	m_Pos = camera->getPossition();
	if (State < 1)
	{
		m_animation->drawCurrentFrame(m_Pos, BOTTOMLEFT, SCALE_NO, D3DCOLOR_XRGB(255, 255, 255), TRANSLATE_NO, ANGLE_NO, true);
		return;
	}
	row = -int(camera->getPossition().y) / m_animation->getFrameWidth();
	column = int(camera->getPossition().x) / m_animation->getFrameHeight();

	
	y = m_Pos.y + RESOLUTION_HEIGHT;
	x = m_Pos.x;
	float c = m_Pos.x;
	for (int i = 0; i < ScreenRow; i++)
	{

		for (int j = 0; j < ScreenColumn; j++)
		{
			if (!(RowMatrix - row + i < 0 || RowMatrix - row + i >= RowMatrix))
			{
				m_Pos.x = x;
				m_Pos.y = y;
				int a = TileMap[RowMatrix - row + i][column + j];

				m_animation->setCurrentIndex(TileMap[RowMatrix - row + i][column + j]);
				m_animation->drawCurrentFrame(m_Pos);
				x = x + m_animation->getFrameHeight();
			}

		}

		y = y - m_animation->getFrameHeight();
		x = c;
	}
}
