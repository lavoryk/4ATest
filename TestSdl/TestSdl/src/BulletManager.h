#pragma once
#include "math/Vector2.h"
#include "Wall.h"
#include "Bullet.h"
class BulletManager
{
public:
	static void Init();
	static void Deinit();
	static BulletManager* GetInstance();
	void Update(float time);
	void Fire(const oxygine::Vector2& pos, const oxygine::Vector2& dir, float speed/*m/s*/, float time, float life_time);
	const std::vector<std::shared_ptr<Wall>>& GetWalls() const
	{
		return m_walls;
	}
	const std::deque<std::shared_ptr<Bullet>>& GetBullets() const
	{
		return m_bullets;
	}
private:
	static bool CheckPartitioning(const oxygine::Vector2& point2Check, float a, float b, float d);
	BulletManager();
	~BulletManager();
	static BulletManager* m_pInstance;
	std::vector<std::shared_ptr<Wall>> m_walls;
	std::deque<std::shared_ptr<Bullet>> m_bullets;
	std::deque<std::shared_ptr<Bullet>> m_newBullets;
	std::mutex m_bulletsMutex;
};