#ifndef _CUBO_H
#define _CUBO_H

#include "objeto3D.h"
using namespace std;

class Cubo : public Objeto3D {

private:
    float lado;
    void asignaCoordenadas(void);

public:
    Cubo(float longitud, GLubyte red, GLubyte green, GLubyte blue);
    void setLado(float longitud);
    float getLado(void);
};

#endif
