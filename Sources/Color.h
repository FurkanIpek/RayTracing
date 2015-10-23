#ifndef COLOR_H
#define COLOR_H

#include <string>

class Color {
private:
	int red, green, blue;
	double alpha;

public:
	Color();
	Color (int, int, int, double);
	int getRed() { return red; }
	int getGreen() { return green; }
	int getBlue() { return blue; }
	double getAlpha() { return alpha; }
	
	int setRed(int redValue) { red = redValue; }
	int setGreen(int greenValue) { green = greenValue; }
	int setBlue(int blueValue) { blue = blueValue; }
	double setAlpha(double alphaValue) { alpha = alphaValue; }
	
	int brightness();
	Color colorScalar(double scalar);
	Color colorAdd(Color color);
	Color colorMultiply(Color color);
	Color colorAverage(Color color);
	Color clip();

	static Color DetectColor(std::string, double);

};

#endif