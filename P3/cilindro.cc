#include "cilindro.h"

Cilindro::Cilindro(vert alt, vert rad, vert num_rev, color r, color g, color b){

	altura = alt;
	radio = rad;

	//Perfil inicial
	perfil_inicial = {radio,0,0,
			radio,altura,0};

	// Asignar atributos
	numero_revoluciones = num_rev;
	eje_rotacion = 'Y';
	ver_tapa_sup = false;
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