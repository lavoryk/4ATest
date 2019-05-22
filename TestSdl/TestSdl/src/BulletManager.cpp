#include "pch.h"
#include "BulletManager.h"
#include "Consts.h"

BulletManager* BulletManager::m_pInstance = nullptr;
void BulletManager::Init()
{
	assert(m_pInstance == nullptr);
	m_pInstance = new BulletManager();
}

void BulletManager::Deinit()
{
	assert(m_pInstance != nullptr);
	delete m_pInstance;
}

BulletManager* BulletManager::GetInstance()
{
	return m_pInstance;
}

BulletManager::BulletManager()
{
	const size_t initiallWallCnt = 10;
	m_walls.reserve(initiallWallCnt);
	for (int i = 0; i < initiallWallCnt; ++i)
	{
		LineSegment2 line;
		do
		{
			for (auto& point : line.points)
			{
				point.x = 0.3f * METER_WIDTH + std::rand() % static_cast<int>(0.7f * METER_WIDTH);
				point.y = static_cast<float>(std::rand() % static_cast<int>(METER_HEIGHT));
			}
			if (line.lenghth() < 0)
			{
				std::swap(line.p1, line.p2);
			}

		} while (line.lenghth() < 10);
		
		m_walls.push_back(std::make_shared<Wall>(line));
	}
}

BulletManager::~BulletManager()
{

}

void BulletManager::Update(float time)
{
	for (auto& bullet : m_bullets)
	{
		bullet->GetState()->Update(time);
	}
	
	m_bullets.erase(
		std::remove_if(m_bullets.begin(), m_bullets.end(),
			[](const auto& pBullet) { return pBullet->GetDestroyed(); }),
		m_bullets.end());
	
	m_walls.erase(
		std::remove_if(m_walls.begin(), m_walls.end(),
			[](const auto& pWall) { return pWall->GetDestroyed(); }),
		m_walls.end());

	{
		std::lock_guard<std::mutex> lock(m_bulletsMutex);
		m_bullets.insert(m_bullets.begin(), m_newBullets.begin(), m_newBullets.end());
		m_newBullets.clear();
	}
}

void BulletManager::Fire(const oxygine::Vector2& pos, const oxygine::Vector2& dir, float speed, float time, float life_time)
{
	// https://en.wikipedia.org/wiki/Muzzle_velocity
	// I assume max Muzzle velocity is High velocity
	// Based on the article above it will be 1524.0f m/s
	assert(!(speed > 1524.0f));

	std::cout << "---- FIRE ----" << std::endl;
	// TODO: custom allocator
	auto pBullet = std::make_shared<Bullet>(speed, time, life_time, pos, dir);
	{
		std::lock_guard<std::mutex> lock(m_bulletsMutex);
		m_newBullets.push_back(pBullet);
	}	
}

bool BulletManager::CheckPartitioning(const oxygine::Vector2& point2Check, float a, float b, float d)
{
	return a * point2Check.x + b * point2Check.y - d > 0;
}
