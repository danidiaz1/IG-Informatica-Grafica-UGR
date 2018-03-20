#include <cstdio>
#include <GL/gl.h>
#include <GL/glut.h>
#include "objeto3D.h"
#include <iostream>
#include <algorithm>
#include <cmath>

void Objeto3D::dibujar(GLenum mode)
{
	if (mode == GL_POINT)
		glPointSize(2.5);

 	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT, mode);

	glEnableClientState( GL_COLOR_ARRAY );
	glEnableClientState( GL_VERTEX_ARRAY ); // habilitar ’vertex arrays’

	glColorPointer( 3, GL_UNSIGNED_BYTE, 0, &colores[0] );
	// especificar puntero a vector	 de coords. de vértices
	glVertexPointer( 3, GL_FLOAT, 0, &vertices[0] );

	// dibujar usando vértices indexados
	glDrawElements( GL_TRIANGLES, caras.size(),
	GL_UNSIGNED_INT, &caras[0] ) ;

	glDisableClientState( GL_COLOR_ARRAY );
	glDisableClientState( GL_VERTEX_ARRAY );
}

void Objeto3D::verVectores(void){

	cout << endl << "Vertices: " << endl;
	cout << "size = " << vertices.size() << endl;
	for (int i=0; i < vertices.size(); i++)
		cout << vertices[i] << " ";

	cout << endl << endl << "Caras: " << endl;
	cout << "size = " << caras.size() << endl;
	for (int i=0; i < caras.size(); i++)
		cout << caras[i] << " ";

}

void Objeto3D::asignaColores(color red, color green, color blue){
	colores.clear();
	r = red;
	g = green;
	b = blue;
	for (int i = 0; i < vertices.size(); i++){
		colores.push_back(r);
		colores.push_back(g);
		colores.push_back(b);
	}
}

void Objeto3D::asignaVectoresAjedrez(void){

	for (int i = 0; i < caras.size(); i+=3){
		if (i%2 == 0){
			caras_pares.push_back(caras.at(i));
			caras_pares.push_back(caras.at(i+1));
			caras_pares.push_back(caras.at(i+2));
		}
		else{
			caras_impares.push_back(caras.at(i));
			caras_impares.push_back(caras.at(i+1));
			caras_impares.push_back(caras.at(i+2));
		}
	}

	for (int i = 0; i < vertices.size(); i++)
	{
		colores_pares.push_back(255);
		colores_pares.push_back(255);
		colores_pares.push_back(0);
	
		colores_impares.push_back(0);
		colores_impares.push_back(0);
		colores_impares.push_back(0);
	}
}

void Objeto3D::dibujarAjedrez(void)
{

	glEnable(GL_CULL_FACE);

	glEnableClientState( GL_VERTEX_ARRAY ); // habilitar ’vertex arrays’
	glEnableClientState( GL_COLOR_ARRAY );

	// especificar puntero a vector	 de coords. de vértices
	glVertexPointer( 3, GL_FLOAT, 0, &vertices[0] );

	// dibujar caras pares
	glColorPointer( 3, GL_UNSIGNED_BYTE, 0, &colores_pares[0] );
	glDrawElements( GL_TRIANGLES, caras_pares.size(),
	GL_UNSIGNED_INT, &caras_pares[0] ) ;

	// dibujar caras impares
	glColorPointer( 3, GL_UNSIGNED_BYTE, 0, &colores_impares[0] );
	glDrawElements( GL_TRIANGLES, caras_impares.size(),
	GL_UNSIGNED_INT, &caras_impares[0] ) ;

	glDisableClientState( GL_COLOR_ARRAY );
	glDisableClientState( GL_VERTEX_ARRAY );
}


void Objeto3D::calcularBoundingBox(void){

	vert x_menor = vertices[0], y_menor = vertices[1], z_menor = vertices[2];
	vert x_mayor = x_menor, y_mayor = y_menor, z_mayor = z_menor;
	vert x,y,z;
	// Calculo del vértice mayor y menor
	for (int i = 3; i < vertices.size(); i+=3)
	{

		x = vertices[i];
		y = vertices[i+1];
		z = vertices[i+2];
		if (x<x_menor) x_menor = x;
		if (y<y_menor) y_menor = y;
		if (z<z_menor) z_menor = z;
		if (x>x_mayor) x_mayor = x;
		if (y>y_mayor) y_mayor = y;
		if (z>z_mayor) z_mayor = z;

	}

	min.push_back(x_menor);
	min.push_back(y_menor);
	min.push_back(z_menor);

	max.push_back(x_mayor);
	max.push_back(y_mayor);
	max.push_back(z_mayor);

	// Cálculo del centro de la figura mediante el calculo del punto medio del segmento
	// dado por los vertices mayor y menor del bounding box

	centro.push_back((max[0]+min[0])/2);
	centro.push_back((max[1]+min[1])/2);
	centro.push_back((max[2]+min[2])/2);

	// Cálculo de la anchura, altura y profundidad de la figura haciendo la distancia
	// entre las coordenadas x, y, z máximas y mínimas.

	anchura = max[0] - min[0];
	altura = max[1] - min[1];
	profundidad = max[2] - min[2];

	// Cálculo de la distancia del centro de la figura al origen
	distancia_origen = sqrt( pow(max[0]-min[0],2) + pow(max[1]-min[1],2) + pow(max[2]-min[2],2) ); 

}

void Objeto3D::transformacionRotacion(vert x, vert y, vert z,
		vert & xprima, vert & yprima, vert & zprima, vert angulo, char eje_rotacion){

	vert angulo_radianes = angulo*PI/180;

	vert sen = sin(angulo_radianes);
	vert coseno = cos(angulo_radianes);
	char eje = toupper(eje_rotacion);

	switch (eje_rotacion){
		case 'X': xprima = x;
				yprima = coseno*y - sen*z;
				zprima = sen*y + coseno*z;
		break;

		case 'Y': xprima = coseno*x + sen*z;
				yprima = y;
				zprima = -1*sen*x + coseno*z;
		break;

		case 'Z': xprima = coseno*x - sen*y;
				yprima = sen*x + coseno*y;
				zprima = z;
		break;
	}
}


void Objeto3D::transformacionEscalado(vert x, vert y, vert z){
	
	double vert_x,vert_y,vert_z;
	
	for (int i = 0; i < vertices.size(); i+=3)
	{
		vert_x= vertices[i];
		vert_y= vertices[i+1];
		vert_z= vertices[i+2];
		vertices[i] = vert_x * x;
		vertices[i+1] = vert_y * y;
		vertices[i+2] = vert_z * z;
	}
}

void Objeto3D::transformacionTraslacion(vert x, vert y, vert z){
	vert vert_x,vert_y,vert_z;
	
	for (int i = 0; i < vertices.size(); i+=3)
	{
		vert_x= vertices[i];
		vert_y= vertices[i+1];
		vert_z= vertices[i+2];

		vertices[i] = vert_x + x;
		vertices[i+1] = vert_y + y;
		vertices[i+2] = vert_z + z;
	}
}