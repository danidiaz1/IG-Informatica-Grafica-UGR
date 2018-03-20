#ifdef _WIN32
#include <windows.h>
#endif
#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "escena.h"

Escena::Escena(){
    Front_plane=50; // A que distancia del ojo empieza a ver la cámara
    Back_plane=2000;
    Observer_distance = 4*Front_plane; // Distancia del observador al primer plano
    Observer_angle_x = Observer_angle_y=0;
    ejes.changeAxisSize(5000); // Tamanio de los ejes
    cubo = new Cubo(50.0, 0, 255, 0);
    tetraedro = new Tetraedro(50.0, 0, 255, 0);
    //dobleTetraedro = new DobleTetraedro(50.0, 0, 255, 0);
    char *archivoPLY="../Modelos_ply/modelos_ply/balance.ply";
    char *archivo_rev="../Modelos_ply/revolucion/rev1.ply";
    //char *archivo_shuriken="../Modelos_ply/modelos_ply/Shuriken1.ply";
    char eje_rotacion='Y';
    ply = new ObjetoPLY(archivoPLY, 0, 255, 0);
    //shuriken = new ObjetoPLY(archivo_shuriken, 0, 255, 0);
    rev = new ObjetoDeRevolucion(archivo_rev,10,eje_rotacion,0,255,0,true);
    androide = new Androide();
    mano = new Mano();
    semiesfera = new Semiesfera(50,3,0,255,0);
    // Para probar la creación del objeto de revolución con un vector
    vector< vert > vec = {
    	0, -0.1, 0,
    	0.7, -0.1, 0,
    	1,	0,	0,
    	1.1, 0, 0, 
    	1,	-0.5, 0,
    	0.5, -1, 0,
    	1, -2, 0,
    	1.5, -3, 0,
		1.5, -4, 0,
		1.5, -5, 0,
		1.5, -6, 0,
		1.3, -6, 0,
		1.3, -5, 0,
		0.8, -4, 0,
		0, -3, 0,

	};
    rev2 = new ObjetoDeRevolucion(vec,10,eje_rotacion,0,255,0,false);
    rev->transformacionEscalado(60.0,60.0,60.0);
    rev2->transformacionEscalado(20.0,20.0,20.0);


    objetoActivo = mano;
    draw_mode = GL_FILL;
    ajedrez = v_animar = false;
    v_animar_mano = true;
    z=0;

}

void Escena::inicializar(int UI_window_width,int UI_window_height) {

	glClearColor(1,1,1,1);// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable(GL_DEPTH_TEST);	// se habilita el z-bufer

	this->change_projection();
	Width=UI_window_width/10;
	Height=UI_window_height/10;
	glViewport(0,0,UI_window_width,UI_window_height);

}


//**************************************************************************
// Funcion que dibuja objetos en la escena
//***************************************************************************

void Escena::draw_objects() {

	if (ajedrez && objetoActivo != rev && objetoActivo != rev2 && objetoActivo != androide
		&& objetoActivo != mano)
		objetoActivo -> dibujarAjedrez();
	else if (objetoActivo == rev){
		if (!ajedrez)
			rev -> dibujar(draw_mode);
		if (ajedrez)
			rev -> dibujarAjedrez();
	} else if (objetoActivo == rev2){
		if (!ajedrez)
			rev2 -> dibujar(draw_mode);
		if (ajedrez)
			rev2 -> dibujarAjedrez();
	} else if (objetoActivo == androide){
		if (!ajedrez)
			androide -> dibujar(draw_mode);
		if (ajedrez)
			androide -> dibujarAjedrez();
	} else if (objetoActivo == mano){
		if (!ajedrez)
			mano -> dibujar(draw_mode);
		if (ajedrez)
			mano -> dibujarAjedrez();
	}
	else
		objetoActivo -> dibujar(draw_mode);

	
}


void Escena::dibujar() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
	draw_axis();
	draw_objects();

}

int Escena::teclaPulsada(unsigned char Tecla1,int x,int y) {

	//std::cout << "Tecla" << Tecla1<< std::endl;
	unsigned char Tecla1mayus = toupper(Tecla1);
	float nuevo_num_revoluciones,velocidad,nueva_velocidad;
	float incremento_velocidad = 0.01;
	switch (Tecla1mayus){

		case 'C': objetoActivo = cubo;
			return 0;
		case 'A': objetoActivo = androide;
			return 0;
		case 'T': objetoActivo = tetraedro;
			return 0;
		case 'P': objetoActivo = ply;
			return 0;
		case 'R': objetoActivo = rev;
			return 0;
		case 'J': objetoActivo = mano;
			return 0;
		case '+':
			velocidad = mano -> getVelocidad();
			nueva_velocidad = velocidad+incremento_velocidad;
			mano->setVelocidad(nueva_velocidad);
			
			return 0;
		case '-':
			velocidad = mano -> getVelocidad();
			nueva_velocidad = velocidad-incremento_velocidad;
			if (nueva_velocidad >=0)
				mano->setVelocidad(nueva_velocidad);
			return 0;
		case 'Z':
			if (z == 0){
				rev -> verTapas(true,false);
				rev2 -> verTapas(true,false);
				z=1;
			}
			else if (z == 1){
				rev -> verTapas(false,true);
				rev2 -> verTapas(false,true);
				z=2;
			} else if (z == 2){
				rev -> verTapas(false,false);
				rev2 -> verTapas(false,false);
				z= 3;
			} else if (z==3){
				rev -> verTapas(true,true);
				rev2 -> verTapas(true,true);
				z = 0;
			}
			return 0;
		case 'S':
			if (v_animar){
				v_animar = false;
			} else
				v_animar = true;
			return 0;
		case 'E': objetoActivo = rev2;
			return 0;
		case 'B':
			if (objetoActivo == rev){
			nuevo_num_revoluciones = rev -> getNumeroRevoluciones() +2;
				if (nuevo_num_revoluciones >=0)
					rev -> setNumeroRevoluciones(nuevo_num_revoluciones);

				rev -> transformacionEscalado(60.0, 60.0, 60.0);
			}
			else if (objetoActivo == rev2)
			{
				nuevo_num_revoluciones = rev2 -> getNumeroRevoluciones() +2;
				if (nuevo_num_revoluciones >=0)
					rev2 -> setNumeroRevoluciones(nuevo_num_revoluciones);
				rev2 -> transformacionEscalado(20.0, 20.0, 20.0);
			}
			return 0;
		case 'V':
			if (objetoActivo == rev){
				nuevo_num_revoluciones = rev -> getNumeroRevoluciones() -2;
				if (nuevo_num_revoluciones >=0)
					rev -> setNumeroRevoluciones(nuevo_num_revoluciones);
				rev -> transformacionEscalado(60.0, 60.0, 60.0);
			} 
			else if (objetoActivo == rev2)
			{
				nuevo_num_revoluciones = rev2 -> getNumeroRevoluciones() -2;
				if (nuevo_num_revoluciones >=0)
					rev2 -> setNumeroRevoluciones(nuevo_num_revoluciones);
				rev2 -> transformacionEscalado(20.0, 20.0, 20.0);
			}
			return 0;
		case 'Q': return 1;
		default: return 0;
	}
}

void Escena::teclaEspecial(int Tecla1,int x,int y) {

	switch (Tecla1){
		case GLUT_KEY_LEFT:Observer_angle_y--;break;
		case GLUT_KEY_RIGHT:Observer_angle_y++;break;
		case GLUT_KEY_UP:Observer_angle_x--;break;
		case GLUT_KEY_DOWN:Observer_angle_x++;break;
		case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
		case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
		case GLUT_KEY_F1: draw_mode = GL_LINE;ajedrez = false;break;
		case GLUT_KEY_F2: draw_mode = GL_POINT;ajedrez = false;break;
		case GLUT_KEY_F3: draw_mode = GL_FILL; ajedrez = false;break;
		case GLUT_KEY_F4: ajedrez = true;break;
	}

	//std::cout << Observer_distance << std::endl;
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void Escena::change_projection()  {
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glFrustum(-Width,Width,-Height,Height,Front_plane,Back_plane);
}


void Escena::redimensionar(int newWidth,int newHeight) {
change_projection();
Width=newWidth/10;
Height=newHeight/10;
glViewport(0,0,newWidth,newHeight);
}


//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************



void Escena::change_observer() {

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}


//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void Escena::draw_axis()
{
ejes.draw();
}

/*Androide* Escena::getAndroide(void){
     	return androide;
}*/

void Escena::animar()
{
	if (v_animar){
		androide->animar();
		
		//if (v_animar_mano)
			mano->animar();

		/*float rot_antebrazo_x = mano->getRotAntebrazoX();

		if (rot_antebrazo_x == -90)
			v_animar_mano = false;*/
		
	}
}


Escena::~Escena()
{
	delete cubo;
	delete tetraedro;
	delete ply;
	delete rev;
	delete semiesfera;
	delete androide;
	delete mano;
	mano = 0;
	androide = 0;
	semiesfera = 0;
	ply=0;
	rev=0;
	cubo = 0;
	tetraedro = 0;
	objetoActivo = 0;
}

