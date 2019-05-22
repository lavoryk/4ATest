#include "pch.h"
#include "Bullet.h"
#include "states/WaitBulletState.h"
#include "states/FlyBulletState.h"
#include "states/NullBulletState.h"

Bullet::Bullet(
	float speed,
	float time,
	float lifeTime,
	const oxygine::Vector2& pos,
	const oxygine::Vector2& dir) :
	m_destroyed(false),
	m_pos(pos)
{
	if (time > 0)
	{
		// TODO: custom allocator
		m_stateQueue.push(std::make_unique<WaitBulletState>(this, time));
	}
	if (lifeTime > 0)
	{
		// TODO: custom allocator
		m_stateQueue.push(std::make_unique<FlyBulletState>(this, lifeTime, speed, dir));
	}
	m_stateQueue.push(std::make_unique<NullBulletState>(this));
	SetNextState();
}

void Bullet::SetNextState()
{
	if (!m_stateQueue.empty())
	{
		m_pState = std::move(m_stateQueue.front());
		m_pState->Init();
		m_stateQueue.pop();
	}
	
}