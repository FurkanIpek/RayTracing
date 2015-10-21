#include "Sources/FileHandler.h"
#include "Sources/ImageRender.h"

#include <iostream>
#include <math.h>
#include <string>
#include <time.h>

using std::cout;
using std::cin;
using std::string;

int main(int argc, char* argv [])
{
	string file_name = "image.prop";
	if ( argc < 2 )
		cout << "Default file name: image.prop\n";
	else
		file_name = argv[1];

	FileHandler* f_handler = new FileHandler(file_name);

	ImageRender render_machine(*f_handler);

	clock_t t1, t2;
	t1 = clock();

	render_machine.Render();
	t2 = clock();

	float diff = ((float)t2 - (float)t1)/1000;
	std::cout << "Total time elapsed while rendering: " << diff  << std::endl;

	string c;
	cin >> c;

	delete f_handler;

	return 0;
}