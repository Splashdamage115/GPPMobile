#ifndef SIMPLE_MATHS_H
#define SIMPLE_MATHS_H

#include "Resources.h"

class math 
{
public:
	static inline bool coordInBox(Vector2 t_point, Vector2 boxPos, Vector2 boxSize)
	{
		return (t_point.x >= boxPos.x && t_point.x <= boxPos.x + boxSize.x &&
			    t_point.y >= boxPos.y && t_point.y <= boxPos.y + boxSize.y);
	}
	template <typename T>
	static inline bool coordInBox(T x, T y, T boxX, T boxY, T sizeX, T sizeY)
	{
		Vector2 p; p.x = x; p.y = y;
		Vector2 box; box.x = boxX; box.y = boxY;
		Vector2 size; size.x = sizeX; size.y = sizeY;

		return coordInBox(p, box, size);
	}
	template <typename T> static inline T min(T a, T b) { return (a < b) ? a : b; }
	template <typename T> static inline T max(T a, T b) { return (a > b) ? a : b; }
};
#endif // !SIMPLE_MATHS_H
