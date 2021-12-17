// graphitti-cmake-vs22.cpp : Defines the entry point for the application.
//

#include "graphitti-cmake-vs22.h"
#include <sqlite3.h>

int main()
{
	std::cout << sqlite3_libversion() << '\n';
	return 0;
}
