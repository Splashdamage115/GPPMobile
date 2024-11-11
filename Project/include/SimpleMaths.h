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
	static inline float squareDistancebetweenPoints(Vector2 t_pos1, Vector2 t_pos2){ return ((t_pos2.x - t_pos1.x) * (t_pos2.x - t_pos1.x) + (t_pos2.y - t_pos1.y) * (t_pos2.y - t_pos1.y)); }
	static inline bool coordInCircle(Vector2 t_point, Vector2 circleCenter, float circleRad){ return (squareDistancebetweenPoints(circleCenter, t_point) <= circleRad * circleRad); }
	static float distance(Vector2 t_pos1, Vector2 t_pos2){ return std::sqrt((t_pos1.x - t_pos2.x) * (t_pos1.x - t_pos2.x) + (t_pos1.y - t_pos2.y) * (t_pos1.y - t_pos2.y)); }
	static float radiansToDegrees(float t_radians) { return t_radians * 180.f / PI; }
	static float displacementToDegrees(Vector2 t_displacement)
	{
		float angle = radiansToDegrees(std::atan2f(t_displacement.y, t_displacement.x));
		if (angle < 0.f)
			angle = 360.f + angle;
		if (angle > 360.f)
		{
			angle = angle - 360.f;
		}
		return angle;
	}
	static Vector2 displacement(Vector2 t_loaction, Vector2 t_aim)
	{
		Vector2 displacement; displacement.x = t_aim.x - t_loaction.x; displacement.y = t_aim.y - t_loaction.y;
		float attenuation = std::sqrtf(displacement.x * displacement.x + displacement.y * displacement.y);
		displacement.x = displacement.x / attenuation; displacement.y = displacement.y / attenuation;
		return displacement;
	}
};
#endif // !SIMPLE_MATHS_H
