#include "androide.h"
#include <iostream>
#define ESCALADO_PIERNAS = 0.5

void Androide::dibujarPierna(GLenum mode, bool ajedrez){
	glPushMatrix();
		glTranslatef(0,-4.5,0);
		glPushMatrix();
			glRotatef(180,1,0,0);
			glScalef(0.5, 0.5, 0.5);
			if (ajedrez)
				semiesfera->dibujarAjedrez();
			else
				semiesfera->dibujar(mode);
		glPopMatrix();
		glPushMatrix();
			glScalef(0.5, 4.75, 0.5);
			if (ajedrez)
				cilindro->dibujarAjedrez();
			else
				cilindro->dibujar(mode);
		glPopMatrix();
	glPopMatrix();

}

void Androide::dibujarBrazo(GLenum mode, bool ajedrez){
	glPushMatrix();
		glTranslatef(0,-3.5,0);
		glPushMatrix();
			glScalef(0.5,3.5,0.5);
			if (ajedrez)
				cilindro->dibujarAjedrez();
			else
				cilindro->dibujar(mode);
		glPopMatrix();

		glPushMatrix();
				glRotatef(180,1,0,0);
			glPushMatrix();
				glScalef(0.5,0.5,0.5);
				if (ajedrez)
					semiesfera->dibujarAjedrez();
				else
					semiesfera->dibujar(mode);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
				glTranslatef(0,3.5,0);
			glPushMatrix();
				glScalef(0.5,0.5,0.5);
				if (ajedrez)
					semiesfera->dibujarAjedrez();
				else
					semiesfera->dibujar(mode);
			glPopMatrix();
		glPopMatrix();

	glPopMatrix();
}

void Androide::dibujarCuerpo(GLenum mode, bool ajedrez){
	glPushMatrix();
		glPushMatrix();
			glScalef(5,5,5);
			if (ajedrez)
				cilindro->dibujarAjedrez();
			else
				cilindro->dibujar(mode);

			cilindro->verTapas(true,true);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,4.5,1);
			glPushMatrix();
				glTranslatef(-2.75,0,0);
				glRotatef(rot_brazo_der,1,0,0);
				dibujarBrazo(mode, ajedrez);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(2.75,0,0);
				glRotatef(rot_brazo_izq,1,0,0);
				dibujarBrazo(mode, ajedrez);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}

void Androide::dibujarCabeza(GLenum mode, bool ajedrez){
	glPushMatrix();
		glPushMatrix();
			glTranslatef(0,1.5,0);
			glPushMatrix();
				glTranslatef(-2.5,0,0);
				glRotatef(-135,0,0,1);
				glScalef(0.3,0.3,0.3);
				dibujarPierna(mode,ajedrez);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(2.5,0,0);
				glRotatef(135,0,0,1);
				glScalef(0.3,0.3,0.3);
				dibujarPierna(mode,ajedrez);
			glPopMatrix();
		glPopMatrix();

		glPushMatrix();
			glScalef(5,5,5);
			if (ajedrez)
				semiesfera->dibujarAjedrez();
			else
				semiesfera->dibujar(mode);

			semiesfera->verTapas(true,true);
		glPopMatrix();
	glPopMatrix();
}

void Androide::dibujarCabezaCuerpo(GLenum mode, bool ajedrez){
	glPushMatrix();
		glPushMatrix();
			glTranslatef(0,5.2,0);
			glTranslatef(0,0,rot_cabeza);
			dibujarCabeza(mode,ajedrez);
		glPopMatrix();
		dibujarCuerpo(mode,ajedrez);
	glPopMatrix();
}

void Androide::dibujarAndroide(GLenum mode, bool ajedrez){
	glPushMatrix();
		glTranslatef(0,3.75,0);
		glPushMatrix();
			glTranslatef(-1,0,0);
			glRotatef(rot_pierna_izq,1,0,0);
			dibujarPierna(mode,ajedrez);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1,0,0);
			glRotatef(rot_pierna_der,1,0,0);
			dibujarPierna(mode,ajedrez);
		glPopMatrix();
		dibujarCabezaCuerpo(mode, ajedrez);
	glPopMatrix();

}

Androide::Androide(){
	cilindro = new Cilindro(1,0.5,30,0,255,0);
	semiesfera = new Semiesfera(0.5,30,0,255,0);
	rot_cabeza = rot_brazo_der = rot_brazo_izq = rot_pierna_der = rot_pierna_izq = 0;
}

void Androide::dibujar(GLenum mode){
	glScalef(20,20,20);
	glPushMatrix();
		glTranslatef(0,-5,0);
		dibujarAndroide(mode, false);
	glPopMatrix();
}

void Androide::dibujarAjedrez(void){

	glScalef(20,20,20);
	glPushMatrix();
		glTranslatef(0,-5,0);
		dibujarAndroide(GL_FILL, true);
	glPopMatrix();
}

Androide::~Androide(){
	delete cilindro;
	delete semiesfera;
	cilindro = 0;
	semiesfera = 0;	
}

float Androide::getRotacionCabeza(){
	return rot_cabeza;
}

void Androide::setRotacionCabeza(float rot){
	rot_cabeza = rot;
}

float Androide::getRotacionBrazoIzquierdo(){
	return rot_brazo_izq;
}

void Androide::setRotacionBrazoIzquierdo(float rot){
	rot_brazo_izq = rot;
}

float Androide::getRotacionBrazoDerecho(){
	return rot_brazo_der;
}

void Androide::setRotacionBrazoDerecho(float rot){
	rot_brazo_der = rot;
}

float Androide::getRotacionPiernaDerecha(){
	return rot_pierna_der;
}

void Androide::setRotacionPiernaDerecha(float rot){
	rot_pierna_der = rot;
}

float Androide::getRotacionPiernaIzquierda(){
	return rot_pierna_izq;
}

void Androide::setRotacionPiernaIzquierda(float rot){
	rot_pierna_izq = rot;
}

/*bool cambio_de_sentido_piernas = false;
bool cambio_de_sentido_cabeza = false;*/
void Androide::animar(){
	float rot_pierna_izq, rot_pierna_der, grado_giro_piernas, rot_cabeza, grado_giro_cabeza,
	rot_brazo_izq, rot_brazo_der;
	
	grado_giro_piernas=1;
	grado_giro_cabeza=0.03;
	rot_pierna_izq = getRotacionPiernaIzquierda();
	rot_pierna_der = getRotacionPiernaDerecha();
	rot_brazo_izq = getRotacionBrazoIzquierdo();
	rot_brazo_der = getRotacionBrazoDerecho();
	rot_cabeza = getRotacionCabeza();

	if (rot_pierna_izq <= -45){
		cambio_de_sentido_piernas = true;
	}
	else if (rot_pierna_izq >=45){
		cambio_de_sentido_piernas = false;
	}

	if (cambio_de_sentido_piernas){
		rot_pierna_izq+=grado_giro_piernas;
		rot_pierna_der-=grado_giro_piernas;
		rot_brazo_izq+=grado_giro_piernas;
		rot_brazo_der-=grado_giro_piernas;
	} else {
		rot_pierna_izq-=grado_giro_piernas;
		rot_pierna_der+=grado_giro_piernas;
		rot_brazo_izq-=grado_giro_piernas;
		rot_brazo_der+=grado_giro_piernas;
	}

	if (rot_cabeza <= 0){
		cambio_de_sentido_cabeza = true;
	}
	else if (rot_cabeza >=1){
		cambio_de_sentido_cabeza = false;
	}

	if (cambio_de_sentido_cabeza){
		rot_cabeza+=grado_giro_cabeza;
	} else {
		rot_cabeza-=grado_giro_cabeza;
	}

	setRotacionPiernaIzquierda(rot_pierna_izq);
	setRotacionPiernaDerecha(rot_pierna_der);
	setRotacionBrazoIzquierdo(rot_brazo_izq);
	setRotacionBrazoDerecho(rot_brazo_der);
	setRotacionCabeza(rot_cabeza);


}