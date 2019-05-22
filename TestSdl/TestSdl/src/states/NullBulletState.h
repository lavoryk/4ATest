#pragma once
#include "IBulletState.h"

class NullBulletState: public IBulletState
{
public:
	NullBulletState(Bullet* pBullet);
	~NullBulletState();
	virtual void Init() 
	{
		m_pBullet->SetDestroyed();
	}
	virtual void Update(float time) {}
private:

};

NullBulletState::NullBulletState(Bullet* pBullet) : IBulletState(pBullet)
{
}

NullBulletState::~NullBulletState()
{
}