#include "pch.h"
#include "WaitBulletState.h"
#include "../Bullet.h"

WaitBulletState::WaitBulletState(Bullet* pBullet, float time): 
	IBulletState(pBullet), 
	m_time(time)
{
}

WaitBulletState::~WaitBulletState()
{
}

void WaitBulletState::Init()
{

}

void WaitBulletState::Update(float time)
{
	m_time -= time;
	if (!(m_time > 0))
	{
		m_pBullet->SetNextState();
		// Next state will be FlyBulletState
	}
}