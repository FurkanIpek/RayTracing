#include "Color.h"

Color::Color()
{
	red = 0;
	green = 0;
	blue = 0;
	alpha = 0;
}

Color::Color(int r, int g, int b, int s)
{
	red = r;
	green = g;
	blue = b;
	alpha = s;
}

int Color::brightness() 
{
	return(red + green + blue)/3;
}
	
Color Color::colorScalar(int scalar)
{
	return Color (red*scalar, green*scalar, blue*scalar, alpha);
}
	
Color Color::colorAdd(Color color) 
{
	return Color (red + color.getRed(), green + color.getGreen(), blue + color.getBlue(), alpha);
}
	
Color Color::colorMultiply(Color color)
{
	return Color (red*color.getRed(), green*color.getGreen(), blue*color.getBlue(), alpha);
}
	
Color Color::colorAverage(Color color) 
{
	return Color ((red + color.getRed())/2, (green + color.getGreen())/2, (blue + color.getBlue())/2, alpha);
}

Color Color::clip()
{
	int alllight = red + green + blue;
	int excesslight = alllight - 255;
	if (excesslight > 0) {
		red = red + excesslight*(red/alllight);
		green = green + excesslight*(green/alllight);
		blue = blue + excesslight*(blue/alllight);
	}
	if (red > 255) {red = 255;}
	if (green > 255) {green = 255;}
	if (blue > 255) {blue = 255;}
	if (red < 0) {red = 0;}
	if (green < 0) {green = 0;}
	if (blue < 0) {blue = 0;}
		
	return Color (red, green, blue, alpha);
}

Color Color::DetectColor(std::string str, int alpha)
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

	return Color(0, 204, 204, alpha);
}