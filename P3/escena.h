#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "objeto3D.h"
#include "cubo.h"
#include "tetraedro.h"
//#include "dobleTetraedro.h"
#include "objetoPLY.h"
#include "objetoDeRevolucion.h"
#include "androide.h"
#include "mano.h"
#include "semiesfera.h"

class Escena {
private:
// tamaño de los ejes
#define AXIS_SIZE 5000
Ejes ejes;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Width,Height,Front_plane,Back_plane;

private:
	int z;
	void clear_window();
	void draw_axis();
	void draw_objects();
	GLenum draw_mode;
	bool ajedrez;
	bool cambio_de_sentido_piernas, cambio_de_sentido_cabeza;

//Transformación de cámara
	void change_projection();
	void change_observer();

// Figuras
	Objeto3D *objetoActivo;
	Cubo *cubo;
	Tetraedro *tetraedro;
	//DobleTetraedro *dobleTetraedro;
	ObjetoPLY *ply;
	//ObjetoPLY *shuriken;
	ObjetoDeRevolucion *rev;
	ObjetoDeRevolucion *rev2;
	Androide *androide;
	Semiesfera *semiesfera;
	Mano *mano;

	bool v_animar, v_animar_mano;

	void dispararShuriken(float velocidad);


public:
    Escena();
    //static void animarAndroide(void);
    void animar(void);
    Androide* getAndroide(void);
	void inicializar(int UI_window_width,int UI_window_height);
	void redimensionar(int newWidth,int newHeight) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	int teclaPulsada(unsigned char Tecla1,int x,int y) ;
	void teclaEspecial(int Tecla1,int x,int y);

	~Escena();
};
#endif
