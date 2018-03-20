
#include "semiesfera.h"
#include "iostream"

Semiesfera::Semiesfera(vert rad, vert num_rev, color r, color g, color b){

	radio = rad;

	//Perfil inicial
	calcularPerfilInicial();

	// Asignar atributos
	numero_revoluciones = num_rev;
	eje_rotacion = 'Y';
	ver_tapa_sup = true;
	ver_tapa_inf = false;

	QuitarTapas();

	// Calcular el resto de vértices
	CalcularConjuntoVertices();

	// Calcular las caras
	CalcularConjuntoCaras();
	
	// Calcular el vértice superior e inferior de las tapas y añadirlo al vector de vértices
	CalcularVerticesTapas();

	// Calcular las caras de las tapas superior e inferior y añadirlas al vector de caras
	CalcularCarasTapas();

	// Asignar colores
	asignaColores(r, g, b);

	// Asignar valores para vectores del modo ajedrez
	asignaVectoresAjedrez();
}


void Semiesfera::calcularPerfilInicial(void){
	perfil_inicial.push_back(radio);
	perfil_inicial.push_back(0.0);
	perfil_inicial.push_back(0.0);

	vert x = radio;
	vert y = 0;
	vert z = 0;

	for (int angulo=10; angulo <90; angulo+=10)
	{	
		vert xprima, yprima, zprima;
		transformacionRotacion(x,y,z,xprima,yprima,zprima,angulo,'Z');
		
		perfil_inicial.push_back(xprima);
		perfil_inicial.push_back(yprima);
		perfil_inicial.push_back(0.0);
	}

	perfil_inicial.push_back(0.0);
	perfil_inicial.push_back(radio);
	perfil_inicial.push_back(0.0);
}