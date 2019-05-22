#pragma once
#include "IBulletState.h"
class WaitBulletState : public IBulletState
{
public:
	WaitBulletState(Bullet* pBullet, float time);
	~WaitBulletState();
	virtual void Init();
	virtual void Update(float time);
private:
	float m_time;
};
