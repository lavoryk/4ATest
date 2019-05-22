#include "Vector2.h"
#pragma once
template <typename T>
class LineSegmentT2
{
	typedef oxygine::VectorT2<T> vector2;
	typedef LineSegmentT2<T> line2;
public:
	LineSegmentT2():p1(0, 0), p2(0, 0)
	{
	}

	T lenghth() const
	{
		return p1.distance(p2);
	}

	static bool IntersectPointOfTwoLineSegments(const vector2& p1, const vector2& p2, const vector2& p3, const vector2& p4, vector2& result)
	{
		// http://paulbourke.net/geometry/pointlineplane/
		float denom = ((p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y));
		bool returnVal = false;
		if (denom != 0.0f)
		{
			float ua = ((p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x)) / denom;
			float ub = ((p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x)) / denom;
			result = p1 + (p2 - p1) * ua;
			returnVal = !(ua < 0.0f || ua > 1.0f) && !(ub < 0.0f || ub > 1.0f);
		}
		return returnVal;
	}

	static bool NearestPointOnLineSegment(const vector2& p1, const vector2& p2, const vector2& p3, vector2& result)
	{
		// http://paulbourke.net/geometry/pointlineplane/
		float u = ((p3.x - p1.x) * (p2.x - p1.x) + (p3.y - p1.y) * (p2.y - p1.y)) / (p2 - p1).sqlength();
		result = p1 + (p2 - p1) * u;
		return !(u < 0.0f || u > 1.0f);
	}

	union
	{
		struct
		{
			vector2 p1, p2;
		};
		vector2 points[2];
	};
};

typedef LineSegmentT2<float> LineSegment2;