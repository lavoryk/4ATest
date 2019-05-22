#pragma once
#include "math/Vector2.h"
#include "states/IBulletState.h"
#include <queue>
class Bullet
{
public:
	Bullet(
		float speed,
		float time,
		float lifeTime,
		const oxygine::Vector2& pos,
		const oxygine::Vector2& dir);
	const oxygine::Vector2& GetHitPos() const
	{
		return m_hitPos;
	}
	void SetHitPos(const oxygine::Vector2& hitPos)
	{
		m_hitPos = hitPos;
	}
	const oxygine::Vector2& GetNearestPos() const
	{
		return m_nearestPos;
	}
	void SetNearestPos(const oxygine::Vector2& nearestPos)
	{
		m_nearestPos = nearestPos;
	}
	const oxygine::Vector2& Pos() const
	{
		return m_pos;
	}
	oxygine::Vector2& Pos()
	{
		return m_pos;
	}
	IBulletState* GetState()
	{
		return m_pState.get();
	}
	void SetNextState();
	void SetDestroyed()
	{
		m_destroyed = true;
	}
	bool GetDestroyed() const
	{
		return m_destroyed;
	}
private:
	bool m_destroyed;
	oxygine::Vector2 m_pos;
	oxygine::Vector2 m_hitPos;
	oxygine::Vector2 m_nearestPos;
	std::unique_ptr<IBulletState> m_pState;
	std::queue<std::unique_ptr<IBulletState>> m_stateQueue;
};