#include "objetoDeRevolucion.h"
#include "FilePLY.h"
#include <math.h>
#include <iostream>
#include <cstdio>

ObjetoDeRevolucion::ObjetoDeRevolucion(vector<vert> &v, vert num_revoluciones, char eje, color red, color green, color blue, bool tieneTapas){
	// Cargar perfil inicial
	perfil_inicial = v;

	// Asignar atributos
	numero_revoluciones = num_revoluciones;
	eje_rotacion = eje;
	ver_tapa_sup = true;
	ver_tapa_inf = true;

	// Esta funcion quita las tapas del perfil inicial para que no se repitan
	if (tieneTapas)
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
	asignaColores(red, green, blue);

	// Asignar valores para vectores del modo ajedrez
	asignaVectoresAjedrez();
}

ObjetoDeRevolucion::ObjetoDeRevolucion(char *File_name, vert num_revoluciones, char eje, color red, color green, color blue, bool tieneTapas){

	vector<GLuint> caras_iniciales; // caras del perfil inicial, no las necesitamos, así que se desechan
	// cuando se sale del constructor.

	// Cargar pefil inicial
	FilePLY fichero;

	fichero.open(File_name);
    fichero.read(perfil_inicial, caras_iniciales);

	// Asignar atributos
	numero_revoluciones = num_revoluciones;
	eje_rotacion = eje;
	ver_tapa_sup = true;
	ver_tapa_inf = true;

	// Esta funcion quita las tapas del perfil inicial para que no se repitan al hacer la revolución
	if (tieneTapas)
		QuitarTapas();

	// Calcular el resto de vértices
	CalcularConjuntoVertices();

	// Calcular las caras
	CalcularConjuntoCaras();

	// Calcular el vértice superior e inferior de las tapas y añadirlo al vector de vértices
	CalcularVerticesTapas();

	// Posicionar y escalar el objeto
	calcularBoundingBox();

	// Calcular las caras de las tapas superior e inferior y añadirlas al vector de caras
	CalcularCarasTapas();

	// Asignar colores
	asignaColores(red, green, blue);

	// Asignar valores para vectores del modo ajedrez
	asignaVectoresAjedrez();


}

ObjetoDeRevolucion::ObjetoDeRevolucion(){
	numero_revoluciones = 0;
	eje_rotacion = 'Y';
	ver_tapa_sup = ver_tapa_inf = false;
}

void ObjetoDeRevolucion::CalcularConjuntoVertices(void){ // char eje
	float angulo_rotacion = 360.0/numero_revoluciones*1.0;
	float angulo = angulo_rotacion;

	for (float rotacion = 0; rotacion < numero_revoluciones; rotacion++) // bucle que controla las revoluciones
	{
		// bucle que controla por qué vertice vamos del perfil inicial
		// y realiza las transformaciones de rotación con respecto a un eje de coordenadas
		for (int v = 0; v < perfil_inicial.size(); v+=3)
		{
			vert x = perfil_inicial.at(v);
			vert y = perfil_inicial.at(v+1);
			vert z = perfil_inicial.at(v+2);
			vert xprima, yprima, zprima;
			transformacionRotacion(x,y,z,xprima,yprima,zprima,angulo,eje_rotacion);
			
			vertices.push_back(xprima);
			vertices.push_back(yprima);
			vertices.push_back(zprima);
		}
		angulo+=angulo_rotacion;
		
	}
}

void ObjetoDeRevolucion::CalcularConjuntoCaras(void){
    int tam = perfil_inicial.size()/3; // Numero de vértices del perfil.
    unsigned int num_vert = 0; // Variable que lleva el conteo de los vértices
   							 // del perfil Qj por el que vamos
    
    vector<GLfloat> :: iterator begin = perfil_inicial.begin()+1;
    vector<GLfloat> :: iterator end = perfil_inicial.end()-2;
    
    // Para comprobar el orden en que nos dan los puntos
    if (*begin < *end)
    {
    	// Bucle que lleva el conteo de la revolución por la que vamos
	    for (int i = 1; i < numero_revoluciones; i++){
	        // Bucle que calcula las caras (triángulos) de los perfiles consecutivos Qj y Qj+1
	        for (int j = 1; j < tam; j++){

	            //Primer triángulo entre el perfil Qj Qj+1
	            caras.push_back(num_vert);
	            caras.push_back(num_vert+1+tam);
	            caras.push_back(num_vert+1);
	            

	            //Segundo triángulo entre el perfil Qj Qj+1
	            caras.push_back(num_vert);
	            caras.push_back(num_vert+tam);
	            caras.push_back(num_vert+1+tam);
	            
	            num_vert++;
	        	
	        }
	        num_vert++; // Pasamos al primer vértice del perfil Qj+1,
	    }

	    // Para la última revolución tenemos que calcular las caras entre el perfil Qj+m
	    // Qj0, es decir, entre el último y el primero

	    for (int j = 1; j < tam; j++){

	            //Primer triángulo entre el perfil Qj+m Qj0
	            caras.push_back(num_vert);
	            caras.push_back(j);
	            caras.push_back(num_vert+1);
	            
	            //Segundo triángulo entre el perfil Qj+m Qj0
	            caras.push_back(num_vert);
	            caras.push_back(j-1);
	            caras.push_back(j);
	            
	            num_vert++;	
	    }
	} else {
		for (int i = 1; i < numero_revoluciones; i++){
	        // Bucle que calcula las caras (triángulos) de los perfiles consecutivos Qj y Qj+1
	        for (int j = 1; j < tam; j++){

	            //Primer triángulo entre el perfil Qj Qj+1
	            caras.push_back(num_vert);
	            caras.push_back(num_vert+1);
	            caras.push_back(num_vert+1+tam);
	            
	            

	            //Segundo triángulo entre el perfil Qj Qj+1
	            caras.push_back(num_vert);
	            caras.push_back(num_vert+1+tam);
	            caras.push_back(num_vert+tam);
	           
	            num_vert++;
	        	
	        }
	        num_vert++; // Pasamos al primer vértice del perfil Qj+1,
	    }

	    // Para la última revolución tenemos que calcular las caras entre el perfil Qj+m
	    // Qj0, es decir, entre el último y el primero

	    for (int j = 1; j < tam; j++){

	            //Primer triángulo entre el perfil Qj+m Qj0
	            caras.push_back(num_vert);
	            caras.push_back(num_vert+1);
	            caras.push_back(j);
	            
	            
	            //Segundo triángulo entre el perfil Qj+m Qj0
	            caras.push_back(num_vert);
	            caras.push_back(j);
	            caras.push_back(j-1);
	            
	            
	            num_vert++;	
	    }
	}
}

void ObjetoDeRevolucion::CalcularVerticesTapas(void)
{

	vert x_superior, y_superior, z_superior, x_inferior, y_inferior, z_inferior;
	
	// Calculo del vértice superior e inferior de la tapa según el eje de rotación (x,y,z)
	switch (eje_rotacion){
		case 'X': y_superior = y_inferior = z_superior = z_inferior = 0;

			x_superior = perfil_inicial.at(1);
			x_inferior = perfil_inicial.at(1);
			
			for (int i = 4; i < perfil_inicial.size(); i+=3)
			{
				if (perfil_inicial.at(i) > y_superior)
					x_superior = perfil_inicial.at(i);

				if (perfil_inicial.at(i) < y_inferior)
					x_inferior = perfil_inicial.at(i);
			}

			break; 

		case 'Y': x_superior = x_inferior = z_superior = z_inferior = 0;
		
			y_superior = perfil_inicial.at(1);
			y_inferior = perfil_inicial.at(1);
			
			for (int i = 4; i < perfil_inicial.size(); i+=3)
			{
				if (perfil_inicial.at(i) > y_superior)
					y_superior = perfil_inicial.at(i);

				if (perfil_inicial.at(i) < y_inferior)
					y_inferior = perfil_inicial.at(i);
			}

			break;

		case 'Z': x_superior = x_inferior = y_superior = y_inferior = 0;

			z_superior = perfil_inicial.at(1);
			z_inferior = perfil_inicial.at(1);
			
			for (int i = 4; i < perfil_inicial.size(); i+=3)
			{
				if (perfil_inicial.at(i) > y_superior)
					z_superior = perfil_inicial.at(i);

				if (perfil_inicial.at(i) < y_inferior)
					z_inferior = perfil_inicial.at(i);
			}
			break;
	}


	// Añadimos el vértice de la tapa inferior
	vertices.push_back(x_inferior);
	vertices.push_back(y_inferior);
	vertices.push_back(z_inferior);

	// Añadimos el vértice la tapa superior
	vertices.push_back(x_superior);
	vertices.push_back(y_superior);
	vertices.push_back(z_superior);

}

void ObjetoDeRevolucion::CalcularCarasTapas(void){

	int tam = perfil_inicial.size()/3; // Numero de vértices del pefil.
    cara num_vert = 0; // Variable que lleva el conteo de los vértices
    // del perfil Qj por el que vamos
    cara vert_tapa_inferior = vertices.size()/3-2; // El penúltimo vértice del vector de vértices.
    cara vert_tapa_superior = vertices.size()/3-1; // El último vértice del vector de vértices.

    // Tapa inferior
	for (int j = 1; j < numero_revoluciones; j++){

            caras.push_back(num_vert);
            caras.push_back(vert_tapa_inferior); // El penúltimo vértice, es decir, la tapa inferior
            caras.push_back(num_vert+tam);
            
            num_vert+=tam;
    }

    // Para el último triángulo de la tapa inferior:
    caras.push_back(num_vert);
    caras.push_back(vert_tapa_inferior);
    caras.push_back(0);

    num_vert = tam-1;
    //Tapa superior
    for (int j = 1; j < numero_revoluciones; j++){
            caras.push_back(num_vert+tam);
            caras.push_back(vert_tapa_superior); // El penúltimo vértice, es decir, la tapa inferior
            caras.push_back(num_vert);
            
            num_vert+=tam;
    }

    // Para el último triángulo de la tapa inferior:
    caras.push_back(tam-1);
    caras.push_back(vert_tapa_superior);
    caras.push_back(num_vert);
	
}

void ObjetoDeRevolucion::QuitarTapas(void){
	vert x,y,z;
	// Miramos, según el eje, que haya dos coordenadas con valor 0 para algún vértice. Si
	// esto ocurre, tendremos un vértice la forma x,0,0 o 0,y,0 o 0,0,z
	switch (eje_rotacion){
		case 'X':
			for (int i = 0; (i < perfil_inicial.size()); i+=3){
				y = perfil_inicial.at(i+1);
				z = perfil_inicial.at(i+2);

				if ((y==0) && (z==0)){
					perfil_inicial.erase(perfil_inicial.begin()+i);
					perfil_inicial.erase(perfil_inicial.begin()+i);
					perfil_inicial.erase(perfil_inicial.begin()+i);
				}
			}
		break;

		case 'Y':
			for (int i = 0; (i < perfil_inicial.size()); i+=3){
				x = perfil_inicial.at(i);
				z = perfil_inicial.at(i+2);

				if ((x==0) && (z==0)){
					perfil_inicial.erase(perfil_inicial.begin()+i);
					perfil_inicial.erase(perfil_inicial.begin()+i);
					perfil_inicial.erase(perfil_inicial.begin()+i);
				}
			}
		break;

		case 'Z': 
			for (int i = 0; (i < perfil_inicial.size()); i+=3){
				x = perfil_inicial.at(i);
				y = perfil_inicial.at(i+2);

				if ((x==0) && (y==0)){
					perfil_inicial.erase(perfil_inicial.begin()+i);
					perfil_inicial.erase(perfil_inicial.begin()+i);
					perfil_inicial.erase(perfil_inicial.begin()+i);
				}
			}
		break;
	}
}

void ObjetoDeRevolucion::verTapas(const bool superior, const bool inferior){
	ver_tapa_sup = superior;
	ver_tapa_inf = inferior;
}

void ObjetoDeRevolucion::dibujar(GLenum mode)
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
	
	mostrarTapas();

	glDisableClientState( GL_COLOR_ARRAY );
	glDisableClientState( GL_VERTEX_ARRAY );
}

void ObjetoDeRevolucion::dibujarAjedrez(void){

	glEnable(GL_CULL_FACE);

	glEnableClientState( GL_VERTEX_ARRAY ); // habilitar ’vertex arrays’
	glEnableClientState( GL_COLOR_ARRAY );

	// especificar puntero a vector	 de coords. de vértices
	glVertexPointer( 3, GL_FLOAT, 0, &vertices[0] );

	mostrarTapasAjedrez();

	glDisableClientState( GL_COLOR_ARRAY );
	glDisableClientState( GL_VERTEX_ARRAY );
}

void ObjetoDeRevolucion::mostrarTapas(void){
	if (!ver_tapa_inf && !ver_tapa_sup){ // no ver tapa superior ni inferior
		// Dibujar todas las caras menos las dadas por las últimas 6*numero_revoluciones caras,
		// correspondientes a la tapa inferior y superior
		glDrawElements( GL_TRIANGLES, caras.size()-numero_revoluciones*6,
		GL_UNSIGNED_INT, &caras[0]);
				

	} 
	else if (!ver_tapa_sup){ // ver tapa inferior
		// Dibujar todas las caras menos las dadas por las últimas 3*numero_revoluciones caras,
		// correspondientes a la tapa superior.
		glDrawElements( GL_TRIANGLES, caras.size()-numero_revoluciones*3,
		GL_UNSIGNED_INT, &caras[0]);
				

	}
	else if (!ver_tapa_inf){ // ver tapa superior

		glDrawElements( GL_TRIANGLES, caras.size()-numero_revoluciones*6,
		GL_UNSIGNED_INT, &caras[0]);

		glDrawElements( GL_TRIANGLES, numero_revoluciones*3,
		GL_UNSIGNED_INT, &caras[caras.size()-3*numero_revoluciones]);
		
	}
	else { // ver toda la figura
		glDrawElements( GL_TRIANGLES, caras.size(),
		GL_UNSIGNED_INT, &caras[0] );
	}
}

void ObjetoDeRevolucion::mostrarTapasAjedrez(void){
	if (!ver_tapa_inf && !ver_tapa_sup){ // no ver tapa superior ni inferior
		// dibujar caras pares
		glColorPointer( 3, GL_UNSIGNED_BYTE, 0, &colores_pares[0] );
		glDrawElements( GL_TRIANGLES, caras_pares.size()-numero_revoluciones*3,
		GL_UNSIGNED_INT, &caras_pares[0] );

		// dibujar caras impares
		glColorPointer( 3, GL_UNSIGNED_BYTE, 0, &colores_impares[0] );
		glDrawElements( GL_TRIANGLES, caras_impares.size()-numero_revoluciones*3,
		GL_UNSIGNED_INT, &caras_impares[0] ) ;

	} 
	else if (!ver_tapa_sup){ // ver tapa inferior
		
		// dibujar caras pares
		glColorPointer( 3, GL_UNSIGNED_BYTE, 0, &colores_pares[0] );
		glDrawElements( GL_TRIANGLES, caras_pares.size()-numero_revoluciones*1.5,
		GL_UNSIGNED_INT, &caras_pares[0] ) ;

		// dibujar caras impares
		glColorPointer( 3, GL_UNSIGNED_BYTE, 0, &colores_impares[0] );
		glDrawElements( GL_TRIANGLES, caras_impares.size()-numero_revoluciones*1.5,
		GL_UNSIGNED_INT, &caras_impares[0] ) ;		

	}
	else if (!ver_tapa_inf){ // ver tapa superior
		// dibujar caras pares
		glColorPointer( 3, GL_UNSIGNED_BYTE, 0, &colores_pares[0] );
		glDrawElements( GL_TRIANGLES, caras_pares.size()-numero_revoluciones*3,
		GL_UNSIGNED_INT, &caras_pares[0] ) ;
		glDrawElements( GL_TRIANGLES, numero_revoluciones*1.5,
		GL_UNSIGNED_INT, &caras_pares[caras_pares.size()-1.5*numero_revoluciones] );

		// dibujar caras impares
		glColorPointer( 3, GL_UNSIGNED_BYTE, 0, &colores_impares[0] );
		glDrawElements( GL_TRIANGLES, caras_impares.size()-numero_revoluciones*3,
		GL_UNSIGNED_INT, &caras_impares[0] ) ;
		glDrawElements( GL_TRIANGLES, numero_revoluciones*1.5,
		GL_UNSIGNED_INT, &caras_impares[caras_impares.size()-1.5*numero_revoluciones] ) ;
		
	}
	else { // ver toda la figura
		// dibujar caras pares
		glColorPointer( 3, GL_UNSIGNED_BYTE, 0, &colores_pares[0] );
		glDrawElements( GL_TRIANGLES, caras_pares.size(),
		GL_UNSIGNED_INT, &caras_pares[0] ) ;

		// dibujar caras impares
		glColorPointer( 3, GL_UNSIGNED_BYTE, 0, &colores_impares[0] );
		glDrawElements( GL_TRIANGLES, caras_impares.size(),
		GL_UNSIGNED_INT, &caras_impares[0] ) ;
	}
	
}

void ObjetoDeRevolucion::setNumeroRevoluciones(vert num){

		numero_revoluciones = num;
		vertices.clear();
		caras.clear();
		caras_pares.clear();
		caras_impares.clear();
		colores_pares.clear();
		colores_impares.clear();
		colores.clear();
		// recalculamos los vectores del objeto

		CalcularConjuntoVertices();
		CalcularConjuntoCaras();
		CalcularVerticesTapas();
		CalcularCarasTapas();

		// Asignar colores
		asignaColores(r, g, b);

		// Asignar valores para vectores del modo ajedrez
		asignaVectoresAjedrez();
}

vert ObjetoDeRevolucion::getNumeroRevoluciones(void){
	return numero_revoluciones;
}