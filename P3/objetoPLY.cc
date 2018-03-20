#include "objetoPLY.h"
#include "FilePLY.h"
#include <iostream>
using namespace std;

ObjetoPLY::ObjetoPLY(char *File_name, color red, color green, color blue){
	fichero = new FilePLY();
	fichero->open(File_name);

	fichero->read(vertices,caras);
	asignaColores(red, green, blue);
	
	asignaVectoresAjedrez();
}