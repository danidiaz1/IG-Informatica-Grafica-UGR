#ifndef _TETRAEDRO_H
#define _TETRAEDRO_H

#include "objeto3D.h"
using namespace std;

class Tetraedro : public Objeto3D {

private:
    vert lado;
    void asignaCoordenadas(void);

public:
    Tetraedro(vert longitud, GLubyte red, GLubyte green, GLubyte blue);
    void setLado(vert longitud);
    vert getLado(void);
};

#endif