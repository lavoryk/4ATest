#pragma once
class Bullet;
struct IBulletState
{
	virtual void Init() = 0;
	virtual void Update(float time) = 0;
	virtual ~IBulletState() = default;
	IBulletState(Bullet* pBullet) :m_pBullet(pBullet)
	{
	}	
protected:
	Bullet* const m_pBullet;
};