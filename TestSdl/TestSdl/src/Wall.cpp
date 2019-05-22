#include "pch.h"
#include "Wall.h"

Wall::Wall() :
	m_destroyed(false)
{

}

Wall::Wall(const LineSegment2& line) : 
	m_destroyed(false), 
	m_LineSegment(line)
{

}

const LineSegment2& Wall::GetLineSegment2() const
{
	return m_LineSegment;
}

void Wall::SetLine2(const LineSegment2& line)
{
	m_LineSegment = line;
}
