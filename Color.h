#ifndef COLOR_H
#define COLOR_H

class Color {
private:
	double red, green, blue, special;

public:
	Color();
	Color (double, double, double, double);
	double getRed() { return red; }
	double getGreen() { return green; }
	double getBlue() { return blue; }
	double getSpecial() { return special; }
	
	double setRed(double redValue) { red = redValue; }
	double setGreen(double greenValue) { green = greenValue; }
	double setBlue(double blueValue) { blue = blueValue; }
	double setSpecial(double specialValue) { special = specialValue; }
	
	double brightness();
	Color colorScalar(double scalar);
	Color colorAdd(Color color);
	Color colorMultiply(Color color);
	Color colorAverage(Color color);
	Color clip();

};

#endif