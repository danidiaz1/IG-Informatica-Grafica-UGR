#ifndef _DOBLETETRAEDRO_H
#define _DOBLETETRAEDRO_H

#include "objeto3D.h"
using namespace std;

class DobleTetraedro : public Objeto3D {

private:
    GLdouble lado;
    void verDobleTetraedro(void);

public:
    DobleTetraedro(GLdouble longitud, GLubyte red, GLubyte green, GLubyte blue);
    void verPrimerTetraedro(void);
    void verSegundoTetraedro(void);
    void setLado(GLdouble longitud);
    GLdouble getLado(void);
};

#endif