#include"Funkcje.h"
int main(int argc, char *argv[])/*!< Argumenty na ktorych ma pracowac program sa wrpowadzane z lini polecen */
{
	maraton(argc, argv);
	_CrtDumpMemoryLeaks();
	//program nie posiada wyciekow pamieci co bylo sprawdzane na laboratorium 
	return 0;
}