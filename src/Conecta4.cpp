#include "Conecta4.h"

using namespace std;

int get2Verticales(Tablero& t, int turno);
int get3Horizontales(Tablero& t, int turno);

Conecta4::Conecta4(int f, int c){
  Tablero init(f,c);
  this->states.AsignaRaiz(init);
  ArbolGeneral<Tablero>::Nodo n = this->states.raiz();
  generaArbolEstados(10, 0, n);
}

Conecta4::Conecta4(int prof, Tablero& tablero){
  this->states.AsignaRaiz(tablero);
  ArbolGeneral<Tablero>::Nodo n = this->states.raiz();
  generaArbolEstados(5, 1, n);
}

void Conecta4::generaArbolEstados(int prof, int currentProf, ArbolGeneral<Tablero>::Nodo& n){
  if(currentProf != prof){
    int col = n->etiqueta.GetColumnas();
    ArbolGeneral<Tablero>::Nodo ultimoinsertado;

    for (int i=0; i < col; i++) {
      Tablero aux = n->etiqueta;
      
      if (i == 0) {
	if(aux.colocarFicha(i)){
	  ArbolGeneral<Tablero> newTree(aux);
	  this->states.insertar_hijomasizquierda(n, newTree);
	  ultimoinsertado = this->states.hijomasizquierda(n);
	}
      }else {
	if(aux.colocarFicha(i)){
	  ArbolGeneral<Tablero> newTree(aux);
	  this->states.insertar_hermanoderecha(ultimoinsertado, newTree);
	  ultimoinsertado = this->states.hermanoderecha(ultimoinsertado);
	}
      }

      generaArbolEstados(prof, currentProf+1, ultimoinsertado);
    }
	  
  }
}

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
