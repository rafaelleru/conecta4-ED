#include "Conecta4.h"

using namespace std;

int get2Verticales(Tablero& t, int turno);
int get3Horizontales(Tablero& t, int turno);

Conecta4::Conecta4(int f, int c){
  Tablero init(f,c);
  this->states.AsignaRaiz(init);
}

Conecta4::Conecta4(int prof, Tablero& tablero){
  this->states.AsignaRaiz(tablero);
}

void Conecta4::generaArbolEstados(int prof, int currentProf, ArbolGeneral<Tablero>::Nodo& n){

  if(currentProf != prof){
    //Para cada columna posible
    //Cambio "int" a "unsigned int"
    for (unsigned int i = 0; i < n->etiqueta.GetTablero().size(); i++) {
      Tablero aux = n->etiqueta;
      if(aux.colocarFicha(i)){
	ArbolGeneral<Tablero>::Nodo insertado;
	insertado->etiqueta = aux; //No funciona con el constructor del nodo
	ArbolGeneral<Tablero>::Nodo ultimoinsertado;
	if(i == 0){
	  // this->states.insertar_hijomasizquierda(n, ArbolGeneral<Tablero> insert(aux));
	  // ultimoinsertado = this->states.hijomasizquierda(n);
	  n->izqda = insertado;
	  ultimoinsertado = n->izqda;
	} else {
	  ultimoinsertado->drcha = insertado;
	  ultimoinsertado = ultimoinsertado->drcha;
	  //this->states.insertar_hermanoderecha(ultimoinsertado, ArbolGeneral<Tablero> insert(aux));
	}
	insertado->etiqueta.cambiarTurno();
	generaArbolEstados(prof, currentProf+1, ultimoinsertado);
      }
    } //for
  }//if
}


// Tablero& Conecta4::siguienteMovimiento(){
//   /*
//     Nuestro arbol de estados siempre tendra en su raiz el estado
//     actual del tablero, de modo que solo tenemos que evaluar los nodos
//     que nos indique la profundidad de nuestra heuristica, generar los que falten
//     y al salir del metodo actualizar la raiz de nuestro arbol
//   */
//   int prof = 0;
//   int mejorValoracionNodo = -1;
//   Tablero mejor; //Presenta el mejor movimiento encontrado

//   ArbolGeneral<Tablero>::preorden_iterador it = this->states.beginpreorden();
//   //Esto no se paralelizarlo
//   for (it; it != this->states.endpreorden() && prof != this->profundidad; ++it) {
//     if(it.hermano() == 0){
//       prof++;
//     }
//     int val = evalua((*it)); //Depende de la heuristica varias
// 			     //llamadas pueden ser muy lentas asi que
// 			     //almacenamos el valor para usarlo
// 			     //siempre
//     if(val > mejorValoracionNodo){
//       mejorValoracionNodo = val;
//       mejor = *it;
//     }
    
//   }

//   //Antes de devolver vamos a actualizar nuestro arbol de estados
//   //actualizaArbolEstados();	
//   return mejor;
  
// }

void Conecta4::actualizarEstado(Tablero& n){
  ArbolGeneral<Tablero> aux(n);
  ArbolGeneral<Tablero>::Nodo nueva_raiz = aux.raiz();
  //Esta funcion se va a llamar tras elegir un movimiento por un
  //jugador, con lo cual podria ser viable buscar el hijo que tiene el
  //tablero n el cual contiene el movimiento elegido por el jugador, y
  //no generar de nuevo nodos que ya esten generados
  generaArbolEstados(7, 0, nueva_raiz);
  this->states = aux;
}

const ArbolGeneral<Tablero>& Conecta4::getStates(){
  return this->states;
}
