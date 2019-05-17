#include "Hayabusa.h"

#define PATH_SIMON "res\\images\\ninja.png"
#define VELOCITY 100
#define SIMON_VJUMP 400

Hayabusa::Hayabusa()
{
	m_Id = idPLAYER;
	m_Pos = D3DXVECTOR3(200,200, 0);

	/*m_texture = new fwTexture(PATH_SIMON, D3DCOLOR_XRGB(255, 0, 255));
	m_sprite = new fwSprite(m_texture, D3DXVECTOR3(0, 0, 0), 8, 24, 60, 66);
	m_animation = new fwAnimation(m_sprite, 200); */
	m_animation = RES_INSTANCE->m_animationSimon[_STATE::eSTAND];

}
Hayabusa::~Hayabusa(){
	delete m_texture, m_sprite;
	m_texture = nullptr;
	m_texture = nullptr;
	m_animation = nullptr;
}

Hayabusa::Hayabusa(BoundingBox bb, IDObject idobj)
{
	m_bb = bb;
	m_Id = idobj;
	m_visibleBB = true;

}




void Hayabusa::draw()
{
	//m_visibleBB ? BOUNDINGBOX_DRAW(m_bb, COLOR_RED) : false;

	if (!isleft)	{

		m_animation->drawCurrentFrame(m_Pos, CENTER, SCALE_A(1), D3DCOLOR_XRGB(255, 255, 255), TRANSLATE_NO, ANGLE_NO, true);
	}
	else
		m_animation->drawCurrentFrame(m_Pos, CENTER, SCALE_XY(-1, 1), D3DCOLOR_XRGB(255, 255, 255), TRANSLATE_NO, ANGLE_NO, true);
	m_animation->generateNextIndexHorizontal();
}

void Hayabusa::update(DWORD deltatime)
{
	if (fwGET_KEY(DIK_S) == KEY_UP && fwGET_KEY(DIK_SPACE) == KEY_UP &&
		fwGET_KEY(DIK_A) == KEY_UP && fwGET_KEY(DIK_D) == KEY_UP)
	{

		Stand_SM();
	}

	if (fwGET_KEY(DIK_W) == KEY_DOWN || fwGET_KEY(DIK_W) == KEY_PRESS)
	{
		Jump_SM();

	}

	if (fwGET_KEY(DIK_S) == KEY_DOWN || fwGET_KEY(DIK_S) == KEY_PRESS)
	{
		Sit_SM();

	}

	if (fwGET_KEY(DIK_D) == KEY_DOWN || fwGET_KEY(DIK_D) == KEY_PRESS)
	{

		isleft = false;
		Go_SM();
	}
	if (fwGET_KEY(DIK_A) == KEY_DOWN || fwGET_KEY(DIK_A) == KEY_PRESS)
	{

		isleft = true;
		Go_SM();
	}

	if (fwGET_KEY(DIK_K) == KEY_DOWN || fwGET_KEY(DIK_K) == KEY_PRESS )
	{

	
		Attacking();
	}
	if (fwGET_KEY(DIK_K) == KEY_DOWN || fwGET_KEY(DIK_K) == KEY_PRESS&&fwGET_KEY(DIK_S) == KEY_DOWN || fwGET_KEY(DIK_S) == KEY_PRESS)
	{


		Sit_Attacking();
	}
	 




	
	//m_bb.m_pos.x = m_Pos.x - m_animation->getFrameWidth()+13;
	//m_bb.m_pos.y = m_Pos.y - m_animation->getFrameHeight()+20 ;
	//m_bb.m_height = m_animation->getFrameHeight() -5 ;
	//m_bb.m_width = m_animation->getFrameWidth() -5;

	 
	m_bb.m_pos.x = m_Pos.x - m_animation->getFrameWidth()/2   ;
	m_bb.m_pos.y = m_Pos.y - m_animation->getFrameHeight()/2 +3;
	m_bb.m_height = m_animation->getFrameHeight() -5 ;
	m_bb.m_width = m_animation->getFrameWidth() -5;

}
void Hayabusa::updateCollide(SweepAABB col, DWORD deltatime)
{
	float colTime = 1.0f;

	colTime = col.m_colTime;

	if (col.m_colDirection == eColDirection::TOP)
	{
		m_Pos.y += m_bb.m_vy*colTime*deltatime / 1000;
		m_bb.m_vy = 0;
		return;
	}

	if (col.m_colDirection == eColDirection::BOT)
	{
		m_Pos.y += m_bb.m_vy*colTime*deltatime / 1000;
		m_bb.m_vy = 0;
		return;
	}

	if (col.m_colDirection == eColDirection::LEFT)
	{

		m_Pos.x += m_bb.m_vx*colTime*deltatime / 1000;
		m_bb.m_vx = 0;
		return;
	}

	if (col.m_colDirection == eColDirection::RIGHT)
	{

		m_Pos.x += m_bb.m_vx*colTime*deltatime / 1000;
		m_bb.m_vx = 0;
		return;
	}

	m_Pos.x += m_bb.m_vx*colTime*deltatime / 1000;
	m_Pos.y += m_bb.m_vy*colTime*deltatime / 1000;

	if (m_Pos.x <= 0)
		m_Pos.x = 0;
	m_Pos.y += m_bb.m_vy*colTime*deltatime / 1000;
	if (m_Pos.y > 700)
		m_Pos.y = 700;


}
void Hayabusa::Jump_SM()
{

	
	m_animation = Resources::m_animationSimon[_STATE::eJUMP];
	m_bb.m_vy = _VJUMP;
	
	

}
void Hayabusa::Sit_SM()
{


	m_animation = Resources::m_animationSimon[_STATE::eSIT];
	//m_bb.m_vy = -VELOCITY;
	m_bb.m_vx = 0;

}
void Hayabusa::Go_SM()
{
	m_animation = Resources::m_animationSimon[_STATE::eRUN];
	if (isleft == true)
	{

		m_bb.m_vx = -VELOCITY;
	}
	else
	{

		m_bb.m_vx = VELOCITY;
	}

}
void Hayabusa::Stand_SM()
{
	m_animation = Resources::m_animationSimon[_STATE::eSTAND];
	if (isleft == true)
	{

		m_bb.m_vx = 0;
		//m_bb.m_vy = -300;
	}
	else
	{

		m_bb.m_vx = 0;
		//m_bb.m_vy = -300;
	}

}

// nam them
void Hayabusa::Attacking()
{

	m_animation = Resources::m_animationSimon[_STATE::eAttacking];
	if (isleft == true)
	{

		m_bb.m_vx = 0;
		//m_bb.m_vy = -300;
	}
	else
	{

		m_bb.m_vx = 0;
		//m_bb.m_vy = -300;
	}



}

void Hayabusa::Sit_Attacking()
{



	m_animation = Resources::m_animationSimon[_STATE::eSitAttacking];
	if (isleft == true)
	{

		m_bb.m_vx = 0;
		//m_bb.m_vy = -300;
	}
	else
	{

		m_bb.m_vx = 0;
		//m_bb.m_vy = -300;
	}



}


bool Hayabusa::GetCam()
{
	return (m_Pos.x < 160.0 ? false : true);
}