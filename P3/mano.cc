#include "mano.h"
#include <iostream>

// Inicializacion de constantes estáticas

const vert Mano::ESCALADO_Y_PRIMERA_FALANGE = 1.5;
const vert Mano::ESCALADO_Y_TERCERA_FALANGE = 0.5;
const vert Mano::ESCALADO_X_PALMA = 5;
const vert Mano::ESCALADO_Y_PALMA = 5;

void Mano::dibujarPrimeraFalange(GLenum mode, bool ajedrez){

	glPushMatrix();
		glTranslatef(0,ESCALADO_Y_PRIMERA_FALANGE,0);
		if (ajedrez)
			semiesfera -> dibujarAjedrez();
		else
			semiesfera -> dibujar(mode);
	glPopMatrix();

	glPushMatrix();
		glScalef(1,ESCALADO_Y_PRIMERA_FALANGE,1);
		if (ajedrez)
			cilindro -> dibujarAjedrez();
		else
			cilindro -> dibujar(mode);
	glPopMatrix();

}

void Mano::dibujarSegundaFalange(GLenum mode, bool ajedrez){
	
	glPushMatrix();
		glTranslatef(0,1,0);
		if (ajedrez)
			semiesfera -> dibujarAjedrez();
		else
			semiesfera -> dibujar(mode);
	glPopMatrix();

		if (ajedrez)
			cilindro -> dibujarAjedrez();
		else
			cilindro -> dibujar(mode);

}

void Mano::dibujarTerceraFalange(GLenum mode, bool ajedrez){
	glPushMatrix();
		glTranslatef(0,ESCALADO_Y_TERCERA_FALANGE,0);
		if (ajedrez)
			semiesfera -> dibujarAjedrez();
		else
			semiesfera -> dibujar(mode);
	glPopMatrix();

	glPushMatrix();
		glScalef(1,ESCALADO_Y_TERCERA_FALANGE,1);
		if (ajedrez)
			cilindro -> dibujarAjedrez();
		else
			cilindro -> dibujar(mode);
	glPopMatrix();
}

void Mano::dibujarDedo(int numero, GLenum mode, bool ajedrez){
	glPushMatrix();
	glRotatef(rot_dedos[numero*3+2],1,0,0);
	dibujarPrimeraFalange(mode,ajedrez);
		glPushMatrix();
			glTranslatef(0,1.5,0);
			glRotatef(rot_dedos[numero*3+1],1,0,0);
			dibujarSegundaFalange(mode,ajedrez);
			glPushMatrix();
				glTranslatef(0,1,0);
				glRotatef(rot_dedos[numero*3],1,0,0);
				if (numero == 0){
				glPushMatrix();
					glTranslatef(-0.6,0,0);
					if (!extension_antebrazo)
						dibujarShuriken(mode,ajedrez);
				glPopMatrix();
				}
				dibujarTerceraFalange(mode, ajedrez);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void Mano::dibujarDedoPulgar(GLenum mode, bool ajedrez){
	glPushMatrix();
		glRotatef(rot_dedos[13],1,0,0);
		dibujarPrimeraFalange(mode,ajedrez);
		glPushMatrix();
			glTranslatef(0,1.5,0);
			glRotatef(rot_dedos[12],1,0,0);
			dibujarSegundaFalange(mode,ajedrez);
			if (ajedrez)
				semiesfera -> dibujarAjedrez();
			else
				semiesfera -> dibujar(mode);
		glPopMatrix();
	glPopMatrix();
}

void Mano::dibujarPalma(GLenum mode, bool ajedrez){
	glPushMatrix();
		glScalef(ESCALADO_X_PALMA,ESCALADO_Y_PALMA,2);
		if (ajedrez)
			cubo -> dibujarAjedrez();
		else
			cubo -> dibujar(mode);
	glPopMatrix();
}

void Mano::dibujarAntebrazo(GLenum mode, bool ajedrez){

	glPushMatrix();
		glTranslatef(0,5,0);
		glScalef(3,2,2);
		if (ajedrez)
			semiesfera -> dibujarAjedrez();
		else
			semiesfera -> dibujar(mode);
	glPopMatrix();
	glPushMatrix();
		glScalef(3,5,2);
		if (ajedrez)
			cilindro -> dibujarAjedrez();
		else
			cilindro -> dibujar(mode);
	glPopMatrix();
}

void Mano::dibujarShuriken(GLenum mode, bool ajedrez){
	glPushMatrix();
		glScalef(1,2,2);
		glRotatef(-110,1,0,0);
		glRotatef(90,0,0,1);
		if (rot_antebrazo_x >= grado_disparo && rot_antebrazo_x <=grado_disparo+2)
			glGetFloatv(GL_MODELVIEW_MATRIX, m);
		if (ajedrez)
			shuriken -> dibujarAjedrez();
		else
			shuriken -> dibujar(mode);
	glPopMatrix();
}

void Mano::dibujarMano(GLenum mode, bool ajedrez){

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glRotatef(rot_antebrazo_z,0,0,1);
		glRotatef(rot_antebrazo_y,0,1,0);
		glRotatef(rot_antebrazo_x,1,0,0);
		dibujarAntebrazo(mode,ajedrez);
		glTranslatef(0,5,0);
		glPushMatrix();
			glRotatef(rot_munieca_x,1,0,0);
			dibujarPalma(mode,ajedrez);
			// dedo pulgar
			glPushMatrix();
				glTranslatef(2.5,2,0);
				glRotatef(-90,0,0,1);
				if (ajedrez)
					semiesfera -> dibujarAjedrez();
				else
					semiesfera -> dibujar(mode);
				glScalef(1.1,1,1.1);
				dibujarDedoPulgar(mode,ajedrez);
			glPopMatrix();
			// dedo meñique
			glPushMatrix();
				glTranslatef(-2,ESCALADO_Y_PALMA,0);
				if (ajedrez)
					semiesfera -> dibujarAjedrez();
				else
					semiesfera -> dibujar(mode);
				glScalef(1,0.8,1);
				dibujarDedo(3,mode,ajedrez);
			glPopMatrix();
			// dedo anular
			glPushMatrix();
				glTranslatef(-0.7,ESCALADO_Y_PALMA,0);
				if (ajedrez)
					semiesfera -> dibujarAjedrez();
				else
					semiesfera -> dibujar(mode);
				glScalef(1,0.95,1);
				dibujarDedo(2,mode,ajedrez);
			glPopMatrix();
			// dedo corazon
			glPushMatrix();
				glTranslatef(0.7,ESCALADO_Y_PALMA,0);
				if (ajedrez)
					semiesfera -> dibujarAjedrez();
				else
					semiesfera -> dibujar(mode);
				glScalef(1,1.1,1);
				dibujarDedo(1,mode,ajedrez);
			glPopMatrix();
			// dedo indice
			glPushMatrix();
				glTranslatef(2,ESCALADO_Y_PALMA,0);
				if (ajedrez)
					semiesfera -> dibujarAjedrez();
				else
					semiesfera -> dibujar(mode);
				dibujarDedo(0,mode,ajedrez);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m);
	glPushMatrix();
		glTranslatef(0,0,(shuriken->getTraslacion()));
		glRotatef(shuriken -> getRotacion(),0,1,0);
		if (ajedrez)
			shuriken -> dibujarAjedrez();
		else
			shuriken -> dibujar(mode);
	glPopMatrix();
}

Mano::Mano(){
	// Objetos para dibujar
	cilindro = new Cilindro(1,0.5,30,0,255,0);
	semiesfera = new Semiesfera(0.5,30,0,255,0);
	cubo = new Cubo(1,0,255,0);
	shuriken = new Shuriken(0, 255, 0);

	// Pos inicial
	rot_antebrazo_y = 0;
	rot_antebrazo_x = 0;
	rot_munieca_x = 20;
	rot_antebrazo_z = 90;
	
	for (int i = 0; i <= 13; i++)
		rot_dedos.push_back(50);

	// Variables de animacion
	velocidad = 1;
	grado_contraccion_antebrazo = velocidad*6;
	grado_extension_antebrazo = grado_contraccion_antebrazo/2;
	grado_contraccion_munieca = grado_contraccion_antebrazo/2;
	grado_extension_munieca = grado_contraccion_munieca/2;
	grado_contraccion_dedos = grado_contraccion_antebrazo/2;
	grado_extension_dedos = grado_contraccion_dedos/2;
	extension_antebrazo = false;
	animar_shuriken = false;
	grado_disparo = -84;


}

void Mano::dibujar(GLenum mode){
	glScalef(15,15,15);
	dibujarMano(mode, false);
}

void Mano::dibujarAjedrez(void){
	glScalef(15,15,15);
	dibujarMano(GL_FILL, true);	
}

float Mano::getRotAntebrazoX(void){
	return rot_antebrazo_x;
}


void Mano::animar(){

	if (rot_antebrazo_x <= -90){
		extension_antebrazo = true;
		shuriken->setTraslacion(0);
		shuriken->setRotacion(0);
	}
	else if (rot_antebrazo_x >=30)
		extension_antebrazo = false;
	
	if (extension_antebrazo){
		rot_antebrazo_x=rot_antebrazo_x+grado_extension_antebrazo;
		rot_munieca_x+=grado_extension_munieca;

		for (int i = 0; i <= 13; i++)
			rot_dedos[i]+=grado_extension_dedos;

		
	}
	else{
		rot_munieca_x-=grado_contraccion_munieca;
		rot_antebrazo_x-=grado_contraccion_antebrazo;

		for (int i = 0; i <= 13; i++)
			rot_dedos[i]-=grado_contraccion_dedos;

	}

	if (rot_antebrazo_x >= grado_disparo)
			animar_shuriken = true;

	shuriken->animar(animar_shuriken);
}

float Mano::getVelocidad(void){
	return velocidad;
}

void Mano::setVelocidad(float v){
	velocidad = v;
	grado_contraccion_antebrazo = velocidad*6;
	grado_extension_antebrazo = grado_contraccion_antebrazo/2;
	grado_contraccion_munieca = grado_contraccion_antebrazo/2;
	grado_extension_munieca = grado_contraccion_munieca/2;
	grado_contraccion_dedos = grado_contraccion_antebrazo/2;
	grado_extension_dedos = grado_contraccion_dedos/2;
	shuriken->setVelocidad(v);

}

Mano::~Mano(){
	delete cilindro;
	delete semiesfera;
	delete cubo;
	cubo = 0;
	cilindro = 0;
	semiesfera = 0;	
}