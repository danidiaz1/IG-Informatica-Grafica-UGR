#ifndef _OBJETOPLY_H
#define _OBJETOPLY_H

#include "objeto3D.h"
#include "FilePLY.h"
using namespace std;

class ObjetoPLY : public Objeto3D {
private:
	FilePLY *fichero;


public:
    ObjetoPLY(char *File_name, color red, color green, color blue);
};

#endif