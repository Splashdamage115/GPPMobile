#ifndef COLOUR_H
#define COLOUR_H

#include "Resources.h"
#include "SimpleMaths.h"

struct Colour
{
	bool active = true;
	unsigned char r = 0, g = 0, b = 0, a = 0;

	Colour() {}
	Colour(const Colour& t_rhs) { r = t_rhs.r; g = t_rhs.g; b = t_rhs.b; a = t_rhs.a; }
	Colour(unsigned char t_r, unsigned char t_g, unsigned char t_b, unsigned char t_a = 255) : r(t_r), g(t_g), b(t_b), a(t_a) { }
	bool operator==(const Colour& t_rhs) { return (r == t_rhs.r && g == t_rhs.g && b == t_rhs.b && a == t_rhs.a); }
	void operator=(const Colour& t_rhs) { r = t_rhs.r; g = t_rhs.g; b = t_rhs.b; a = t_rhs.a; }
	void operator=(const Color& t_rhs) { r = t_rhs.r; g = t_rhs.g; b = t_rhs.b; a = t_rhs.a; } // converting from and to raylib colour
	Color rayColor() { Color t; t.r = r; t.g = g; t.b = b; t.a = a; return t; }
};

struct HSV
{
	bool active = true;

	unsigned short h = 0, s = 0, v = 0, a = 255;

	void convertColour(Colour& t_c) {
		float r = t_c.r / 255.0f;
		float g = t_c.g / 255.0f;
		float b = t_c.b / 255.0f;

		float min = math::min(math::min(r, g), b);
		float max = math::max(math::max(r, g), b);

		float delta = max - min;

		if (delta == 0.0f) {
			h = 0; 
			s = 0;
			v = static_cast<unsigned short>(max * 100.0f);
			return;
		}

		// Hue
		if (max == r)
			h = static_cast<unsigned short>(60.0f * fmod(((g - b) / delta), 6.0f));
		else if (max == g) 
			h = static_cast<unsigned short>(60.0f * (((b - r) / delta) + 2.0f));
		else if (max == b)
			h = static_cast<unsigned short>(60.0f * (((r - g) / delta) + 4.0f));


		if (h < 0) {
			h += 360;
		}

		s = static_cast<unsigned short>((max == 0) ? 0 : (delta / max) * 100.0f); // dont calculate if zero (error)
		v = static_cast<unsigned short>(max * 100.0f); // change to percent
	}


	Colour toColour() {
		float hh, p, q, t, ff;
		long i;
		float r, g, b;
		float s = this->s / 100.0f;
		float v = this->v / 100.0f;
		if (s <= 0.0)
		{
			// < is incorrect, just in case
			r = v;
			g = v;
			b = v;
			return Colour(r * 255, g * 255, b * 255, this->a);
		}
		hh = this->h;
		if (hh >= 360.0) hh = 0.0;
		hh /= 60.0;
		i = (long)hh;
		ff = hh - i;
		p = v * (1.0 - s);
		q = v * (1.0 - (s * ff));
		t = v * (1.0 - (s * (1.0 - ff)));
		switch (i)
		{
		case 0:
			r = v;
			g = t;
			b = p;
			break;
		case 1:
			r = q;
			g = v;
			b = p;
			break;
		case 2:
			r = p;
			g = v;
			b = t;
			break;
		case 3:
			r = p;
			g = q;
			b = v;
			break;
		case 4:
			r = t;
			g = p;
			b = v;
			break;
		case 5:
		default:
			r = v;
			g = p;
			b = q;
			break;
		}
		return Colour(r * 255, g * 255, b * 255, this->a);

	}
};

#endif // !COLOUR_H
