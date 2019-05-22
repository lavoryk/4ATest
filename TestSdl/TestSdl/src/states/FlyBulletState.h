#pragma once
#include "IBulletState.h"
#include "../math/Vector2.h"
class Wall;
class FlyBulletState : public IBulletState
{
public:
	FlyBulletState(Bullet *pBullet, float lifeTime, float speed, const oxygine::Vector2& dir);
	~FlyBulletState();
	virtual void Init();
	virtual void Update(float time);
private:
	bool m_hitWall;
	bool m_findWall;
	float m_lifeTime;
	float m_flyTime;
	float m_speed;
	oxygine::Vector2 m_dir;
	oxygine::Vector2 m_wallNormal;
	std::weak_ptr<Wall> m_pWall;
};
