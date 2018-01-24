#include "map_pgm.h"
#include "MRRT.h"
#include <iostream>
#define MI 1

int main()
{
	MRRT map("fr079_binary.jpg",point(398,358),point(266,802));
	map.getPath();
	map.showResult("MRRT2.jpg");
	return 0;
}