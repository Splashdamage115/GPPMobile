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

	unsigned short h = 0, s = 0, v = 0, a = 0;

	void convertColour(Colour& t_c)
	{
		float r = t_c.r / 255.f, g = t_c.g / 255.f, b = t_c.b / 255.f;

		float min = math::min(math::min(r, g), b);
		float max = math::max(math::max(r, g), b);

		h = 0;
		s = 0;

		if (min == max) return; // hue is already set to 0

		float hue = 0.0f;

		if (max == r) hue = (g - b) / (max - min);
		else if (max == g) hue = 2.0f + (b - r) / (max - min);
		else hue = 4.0f + (r - g) / (max - min);

		hue = hue * 60;

		float value = (max + min) / 2.f;
		// chroma / (1 - Math.abs(2 * L - 1));
		float x = std::abs(2 * value - 1);
		float saturation = (max - min) / (1 - x);

		if (hue < 0) hue += 360; // ensure that the value is on the unit circle (360 degrees)
		saturation = saturation * 100.f; // percent conversion
		value = value * 100.f; // percent conversion

		h = static_cast<unsigned short>(hue);
		s = static_cast<unsigned short>(saturation);
		v = static_cast<unsigned short>(value);
	}
};

#endif // !COLOUR_H
