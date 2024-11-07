#ifndef CANVAS_H
#define CANVAS_H

#include "Resources.h"

struct Colour
{
	unsigned char r = 0, g = 0, b = 0, a = 0;

	Colour() {}
	Colour(const Colour& t_rhs){ r = t_rhs.r; g = t_rhs.g; b = t_rhs.b; a = t_rhs.a; }
	Colour(unsigned char t_r, unsigned char t_g, unsigned char t_b, unsigned char t_a = 255) : r(t_r), g(t_g), b(t_b), a(t_b) { }
	bool operator==(const Colour& t_rhs) { return (r == t_rhs.r && g == t_rhs.g && b == t_rhs.b && a == t_rhs.a); }
	void operator=(const Colour& t_rhs) { r = t_rhs.r; g = t_rhs.g; b = t_rhs.b; a = t_rhs.a; }
};

class Canvas
{
public:
	// constructor / deconstructor
	Canvas(); ~Canvas();

	void init();
	void update();
	void render();

private:
	std::vector<Colour> m_pixels;
	Vector2 m_topRight;
	int m_pixelSize = 1;
	Vector2 m_canvasSize;

	// use for moving the canvas around
	Vector2 m_mousePos;
	Vector2 m_mouseStartPos;
	float m_mouseSpeedFactor = 1.f;
};



#endif // !CANVAS_H
