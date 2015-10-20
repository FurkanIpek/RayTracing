#ifndef COLOR_H
#define COLOR_H

#include <string>

class Color {
private:
	int red, green, blue, alpha;

public:
	Color();
	Color (int, int, int, int);
	int getRed() { return red; }
	int getGreen() { return green; }
	int getBlue() { return blue; }
	int getAlpha() { return alpha; }
	
	int setRed(int redValue) { red = redValue; }
	int setGreen(int greenValue) { green = greenValue; }
	int setBlue(int blueValue) { blue = blueValue; }
	int setAlpha(int alphaValue) { alpha = alphaValue; }
	
	int brightness();
	Color colorScalar(int scalar);
	Color colorAdd(Color color);
	Color colorMultiply(Color color);
	Color colorAverage(Color color);
	Color clip();

	static Color DetectColor(std::string, int);

};

#endif