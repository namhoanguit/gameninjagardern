#include "Collision.h"
#include "StaticObject.h"

BoundingBox SweepAABB::GetSweptBroadPhaseBox(BoundingBox box1)
{
	BoundingBox broadphasebox(0, 0, 0, 0);

	broadphasebox.m_pos.x = box1.m_vx > 0 ? box1.m_pos.x : (float)(box1.m_pos.x + box1.m_vx);
	broadphasebox.m_pos.y = box1.m_vy > 0 ? box1.m_pos.y : box1.m_pos.y + (float)box1.m_vy;
	broadphasebox.m_width = box1.m_vx > 0 ? box1.m_vx + box1.m_width : box1.m_width - box1.m_vx;
	broadphasebox.m_height = box1.m_vy > 0 ? box1.m_vy + box1.m_height : box1.m_height - box1.m_vy;

	return broadphasebox;
}

bool SweepAABB::CheckAABB(BoundingBox box1, BoundingBox box2)
{
	return !(box1.m_pos.x + box1.m_width < box2.m_pos.x ||
		box1.m_pos.x > box2.m_pos.x + box2.m_width ||
		box1.m_pos.y + box1.m_height < box2.m_pos.y ||
		box1.m_pos.y > box2.m_pos.y + box2.m_height);
}


eColDirection SweepAABB::AABB(BoundingBox box1, BoundingBox box2)
{
	float l = box2.m_pos.x - (box1.m_pos.x + box1.m_width);
	float r = box1.m_pos.x - (box2.m_pos.x + box2.m_width);
	float t = box1.m_pos.y - (box2.m_height + box2.m_pos.y);
	float b = box2.m_pos.y - (box1.m_height + box1.m_pos.y);

	// check that there was a collision
	if (l > 0 || r > 0 || t > 0 || b > 0)
		return eColDirection::NO;

	// find the offset of both sidessx`
	box1.m_vx -= box2.m_vx;
	box1.m_vy -= box2.m_vy;

	box2.m_vx = box2.m_vy = 0.0f;

	// co va cham khong can biet va cham ben nao
	if (t < 0) return eColDirection::TOP;
	if (l < 0) return eColDirection::LEFT;
	if (r < 0) return eColDirection::RIGHT;
	if (b < 0) return eColDirection::BOT;
}

float SweepAABB::algorithmSweepAABB(BoundingBox box1, BoundingBox box2, float& normalx, float& normaly)
{
	float xInvEntry, yInvEntry;

	float xInvExit, yInvExit;
	if (
		(((box1.m_pos.x + box1.m_width) == box2.m_pos.x) && ((box2.m_pos.y + box2.m_height) == box1.m_pos.y)) ||
		(((box2.m_pos.x + box2.m_width) == box1.m_pos.x) && (box1.m_pos.y == (box2.m_pos.y + box2.m_height))) ||
		(((box1.m_pos.x + box1.m_width) == box2.m_pos.x) && ((box1.m_pos.y + box1.m_height == box2.m_pos.y))) ||
		(((box2.m_pos.x + box2.m_width) == box1.m_pos.x) && ((box1.m_pos.y + box1.m_height == box2.m_pos.y)))
		)
	{
		normalx = normaly = 0;
		return 1;
	}
	// find the distance between the objects on the near and far sides for both x and y
	if (box1.m_vx > 0.0f)
	{
		xInvEntry = box2.m_pos.x - (box1.m_pos.x + box1.m_width);
		xInvExit = (box2.m_pos.x + box2.m_width) - box1.m_pos.x;
	}
	else
	{
		xInvEntry = (box2.m_pos.x + box2.m_width) - box1.m_pos.x;
		xInvExit = box2.m_pos.x - (box1.m_pos.x + box1.m_width);
	}

	if (box1.m_vy > 0.0f)
	{
		yInvEntry = box2.m_pos.y - (box1.m_pos.y + box1.m_height);
		yInvExit = (box2.m_pos.y + box2.m_height) - box1.m_pos.y;
	}
	else
	{
		yInvEntry = (box2.m_pos.y + box2.m_height) - box1.m_pos.y;
		yInvExit = box2.m_pos.y - (box1.m_pos.y + box1.m_height);
	}

	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
	float xEntry, yEntry;
	float xExit, yExit;

	if (box1.m_vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = (float)xInvEntry / box1.m_vx;
		xExit = (float)xInvExit / box1.m_vx;
	}

	if (box1.m_vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = (float)yInvEntry / box1.m_vy;
		yExit = (float)yInvExit / box1.m_vy;
	}

	// find the earliest/latest times of collision
	float entryTime = max(xEntry, yEntry);
	float exitTime = min(xExit, yExit);

	// if there was no collision
	if (entryTime > exitTime || (xEntry < 0.0f && yEntry < 0.0f) || xEntry > 1.0f || yEntry > 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}
	else // if there was a collision
	{
		// calculate normal of collided surface
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f)
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
		}
		else
		{
			if (yInvEntry <= 0.0f)
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
		}

		// return the time of collision
		return entryTime;
	}
}

SweepAABB SweepAABB::checkCollisionBySweeepAABB(BoundingBox box1, BoundingBox box2, DWORD deltatime)
{
	BoundingBox _box1((int)box1.m_pos.x, (int)box1.m_pos.y, box1.m_width, box1.m_height, (box1.m_vx - box2.m_vx)*deltatime / 1000, (box1.m_vy - box2.m_vy)*deltatime / 1000);
	BoundingBox _box2((int)box2.m_pos.x, (int)box2.m_pos.y, box2.m_width, box2.m_height);

	float _normx = 0, _normy = 0;
	float _collisionTime = 1;
	eColDirection _direction = eColDirection::NO;
	// Tạo box mới chu kỳ sau(GetSweepBroadPhaseBox) và kiếm tra box có va chạm hay không(CheckAABB). 
	if (CheckAABB(GetSweptBroadPhaseBox(_box1), _box2) == true)
	{
		_collisionTime = algorithmSweepAABB(_box1, _box2, _normx, _normy);
		if (_normx != 0.0f)
		{
			if (_normx == -1.0f)_direction = eColDirection::LEFT;

			if (_normx == 1.0f)_direction = eColDirection::RIGHT;
		}
		if (_normy != 0.0f)
		{
			if (_normy == 1.0f)_direction = eColDirection::TOP;
			if (_normy == -1.0f)_direction = eColDirection::BOT;

		}
	}

	m_colDirection = _direction;
	m_colTime = _collisionTime;

	return SweepAABB(_direction, _collisionTime);
}



SweepAABB SweepAABB::checkCollisionBySweeepAABB(StaticObject* box1, StaticObject* box2, DWORD deltatime)
{
	return checkCollisionBySweeepAABB(box1->getBoundingBox(), box2->getBoundingBox(), deltatime);
}

SweepAABB::SweepAABB()
{
	m_colDirection = eColDirection::NO;
	m_colTime = 1.0f;
}

SweepAABB::SweepAABB(eColDirection colDirection, float colTime)
{
	m_colDirection = colDirection;
	m_colTime = colTime;
}
SweepAABB SweepAABB::checkCollisionBySweeepAABB_new(StaticObject* box1, StaticObject* box2, DWORD deltatime, float x, float y)
{
	return checkCollisionBySweeepAABB_new(box1->getBoundingBox(), box2->getBoundingBox(), deltatime, x, y);
}
SweepAABB SweepAABB::checkCollisionBySweeepAABB_new(BoundingBox box1, BoundingBox box2, DWORD deltatime,float x,float y)
{
	BoundingBox _box1((int)box1.m_pos.x+x , (int)box1.m_pos.y+y, box1.m_width, box1.m_height, (box1.m_vx - box2.m_vx)*deltatime / 1000, (box1.m_vy - box2.m_vy)*deltatime / 1000);
	BoundingBox _box2((int)box2.m_pos.x, (int)box2.m_pos.y, box2.m_width, box2.m_height);

	float _normx = 0, _normy = 0;
	float _collisionTime = 1;
	eColDirection _direction = eColDirection::NO;
	// Tạo box mới chu kỳ sau(GetSweepBroadPhaseBox) và kiếm tra box có va chạm hay không(CheckAABB). 
	if (CheckAABB(GetSweptBroadPhaseBox(_box1), _box2) == true)
	{
		_collisionTime = algorithmSweepAABB(_box1, _box2, _normx, _normy);
		if (_normx != 0.0f)
		{
			if (_normx == -1.0f)_direction = eColDirection::LEFT;

			if (_normx == 1.0f)_direction = eColDirection::RIGHT;
		}
		if (_normy != 0.0f)
		{
			if (_normy == 1.0f)_direction = eColDirection::TOP;
			if (_normy == -1.0f)_direction = eColDirection::BOT;

		}
	}

	m_colDirection = _direction;
	m_colTime = _collisionTime;

	return SweepAABB(_direction, _collisionTime);
}
