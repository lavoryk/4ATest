#include "pch.h"
#include "FlyBulletState.h"
#include "../Bullet.h"
#include "../BulletManager.h"

FlyBulletState::FlyBulletState(Bullet *pBullet, float lifeTime, float speed, const oxygine::Vector2& dir) : 
	IBulletState(pBullet),
	m_hitWall(false),
	m_findWall(true),
	m_lifeTime(lifeTime),
	m_flyTime(0.0f),
	m_speed(speed),
	m_dir(dir)
{

}

FlyBulletState::~FlyBulletState()
{

}

void FlyBulletState::Init()
{
	m_hitWall = false;
	m_findWall = false;
	float minDistanse = std::numeric_limits<float>::max();
	oxygine::Vector2 minResultOfIntersection;
	// Find nearest wall
	for (const auto& wall : BulletManager::GetInstance()->GetWalls())
	{
		const float distanseP1ToPos = wall->GetLineSegment2().p1.distance(m_pBullet->Pos());
		const float distanseP2ToPos = wall->GetLineSegment2().p2.distance(m_pBullet->Pos());

		const oxygine::Vector2& pos1 = m_pBullet->Pos();
		const oxygine::Vector2  pos2 = m_pBullet->Pos() + m_dir * std::max(distanseP1ToPos, distanseP2ToPos);
		oxygine::Vector2 resultOfIntersection;
		if (LineSegment2::IntersectPointOfTwoLineSegments(wall->GetLineSegment2().p1, wall->GetLineSegment2().p2, pos1, pos2, resultOfIntersection))
		{
			std::cout << resultOfIntersection.x << ", " << resultOfIntersection.y << std::endl;
			float d = pos1.distance(resultOfIntersection);
			if (d < minDistanse)
			{
				minDistanse = d;
				m_hitWall = true;
				minResultOfIntersection = resultOfIntersection;
				m_pWall = wall;
			}
		}
	}
	if (m_hitWall)
	{
		// It was found, thus calculate fly time to the wall
		m_flyTime = minDistanse / m_speed;
		// Calculate normal to the segment
		auto wall = m_pWall.lock();
		oxygine::Vector2 nearestPos;
		auto res = LineSegment2::NearestPointOnLineSegment(wall->GetLineSegment2().p1, wall->GetLineSegment2().p2, m_pBullet->Pos(), nearestPos);
		m_pBullet->SetNearestPos(nearestPos);
		m_pBullet->SetHitPos(minResultOfIntersection);
		m_wallNormal = (nearestPos - m_pBullet->Pos()).normalized();
	}
	else
	{
		m_pBullet->SetNearestPos({ 0.0f, 0.0f });
		m_pBullet->SetHitPos({ 0.0f, 0.0f });
	}
}

void FlyBulletState::Update(float time)
{
	if (m_findWall)
	{
		Init();
	}
	m_lifeTime -= time;
	if (!(m_lifeTime > 0))
	{
		m_pBullet->SetNextState();
		// Next state will be NullBulletState
	}
	else
	{
		m_pBullet->Pos() += m_dir * time * m_speed;
		if (m_hitWall)
		{
			m_flyTime -= time;
			if (!(m_flyTime > 0))
			{
				oxygine::Vector2 oldDir = m_dir;
				if (auto pWall = m_pWall.lock())
				{
					// Reflect
					// http://paulbourke.net/geometry/reflected/
					oxygine::Vector2 r1 = m_dir * -1;
					m_dir = m_dir - m_wallNormal * 2 * m_dir.dot(m_wallNormal);
					// Mark wall as destroyed
					pWall->SetDestroyed(true);
					if (m_flyTime < 0)
					{
						// It is possible bullet may fly through a wall
						// Step back with oldDir to be more close to the hitPos
						m_pBullet->Pos() += oldDir * m_flyTime * m_speed;
						// Step forward with new m_dir
						m_pBullet->Pos() += m_dir * -m_flyTime * m_speed;
					}
				}
				m_findWall = true;
			}
		}
	}
}