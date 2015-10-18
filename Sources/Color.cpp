#include "Color.h"

Color::Color()
{
	red = 0.0;
	green = 0.0;
	blue = 0.0;
	special = 0.0;
}

Color::Color(double r, double g, double b, double s)
{
	red = r;
	green = g;
	blue = b;
	special = s;
}

double Color::brightness() 
{
	return(red + green + blue)/3;
}
	
Color Color::colorScalar(double scalar)
{
	return Color (red*scalar, green*scalar, blue*scalar, special);
}
	
Color Color::colorAdd(Color color) 
{
	return Color (red + color.getRed(), green + color.getGreen(), blue + color.getBlue(), special);
}
	
Color Color::colorMultiply(Color color)
{
	return Color (red*color.getRed(), green*color.getGreen(), blue*color.getBlue(), special);
}
	
Color Color::colorAverage(Color color) 
{
	return Color ((red + color.getRed())/2, (green + color.getGreen())/2, (blue + color.getBlue())/2, special);
}

Color Color::clip()
{
	double alllight = red + green + blue;
	double excesslight = alllight - 3;
	if (excesslight > 0) {
		red = red + excesslight*(red/alllight);
		green = green + excesslight*(green/alllight);
		blue = blue + excesslight*(blue/alllight);
	}
	if (red > 1) {red = 1;}
	if (green > 1) {green = 1;}
	if (blue > 1) {blue = 1;}
	if (red < 0) {red = 0;}
	if (green < 0) {green = 0;}
	if (blue < 0) {blue = 0;}
		
	return Color (red, green, blue, special);
}

Color Color::DetectColor(std::string str, double alpha)
{
	if ( str == "red" )
		return Color(204, 20, 30, alpha);
	else if ( str == "white" )
		return Color(255, 255, 255, alpha);
	else if ( str == "black" )
		return Color(0, 0, 0, alpha);
	else if ( str == "gray" )
		return Color(64, 64, 64, alpha);
	else if ( str == "green" )
		return Color(20, 204, 30, alpha);
	else if ( str == "blue" )
		return Color(30, 20, 204, alpha);
	else if ( str == "purple" )
		return Color(153, 0, 153, alpha);
	else if ( str == "floor" )
		return Color(102, 51, 0, alpha);
}