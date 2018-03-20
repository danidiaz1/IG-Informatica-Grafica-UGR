#ifndef _OBJETO3D_H
#define _OBJETO3D_H

#include <vector>
#include <GL/gl.h>
#include <GL/glut.h>
#include "common.h"
#define PI 3.14159265

using namespace std;

class Objeto3D {
protected:
	vector< vert > vertices;
	vector< cara > caras;
	vector< color > colores;

	// Vectores usados para el dibujado del modo ajedrez
	vector< cara > caras_pares;
	vector< cara > caras_impares;
	vector< color > colores_pares;
	vector< color > colores_impares;

	// colores de la figura
	color r,g,b;

	// parámetros del bounding box
	vector< vert > max,min; // vértice máximo y minimo
	vector< vert > centro; // centro de la figura
	vert anchura, altura, profundidad; // anchura altura y profundidad de la caja
	vert distancia_origen; // distancia del centro de la figura al origen (0,0,0)

	// calcula los parametros del bounding box
	void calcularBoundingBox(void);
	
public:
    void dibujar(GLenum mode = GL_FILL);
    void verVectores(void);
    void asignaColores(color red, color green, color blue);

    void dibujarAjedrez(void);
    void asignaVectoresAjedrez(void);
    // Calcular la transformación de rotación del vertice v(x,y,z) que se almacenará
	// en el vértice vprima(xprima,yprima,zprima) a partir de angulo dado (en radianes)
	// y el eje de rotación.
	void transformacionRotacion(vert x, vert y, vert z,
	vert & xprima, vert & yprima, vert & zprima, vert angulo, char eje_rotacion);
	// Calcular la transformación de escalado del vertice v(x,y,z) 
    void transformacionEscalado(vert x, vert y, vert z);
    // Calcular la traslacion del vertice v(x,y,z)
    void transformacionTraslacion(vert x, vert y, vert z);
};

#endif
