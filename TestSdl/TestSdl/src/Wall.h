#pragma once
#include "math/LineSegment2.h"
class Wall
{
public:
	Wall();
	Wall(const LineSegment2& line);
	const LineSegment2& GetLineSegment2() const;
	void SetLine2(const LineSegment2& line);
	bool GetDestroyed() const
	{
		return m_destroyed;
	}
	void SetDestroyed(bool destroyed)
	{
		m_destroyed = destroyed;
	}
private:
	bool m_destroyed;
	LineSegment2 m_LineSegment;
};