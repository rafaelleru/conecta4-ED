#include "Conecta4.h"

using namespace std;

int Conecta4::evalua(Tablero& t){

  return 10;
}

void Conecta4::generaArbolEstados(int prof, int currentProf, ArbolGeneral<Tablero>::Nodo& n){

  if(currentProf != prof){
    //Para cada columna posible
    for (int i = 0; i < n->etiqueta.GetTablero().size(); i++) {
      Tablero aux = n->etiqueta;
      if(aux.colocarFicha(i)){
	ArbolGeneral<Tablero>::Nodo insertado;
	insertado->etiqueta = aux; //No funciona con el constructor del nodo
	ArbolGeneral<Tablero>::Nodo ultimoinsertado;
	if(i = 0){
	  // this->states.insertar_hijomasizquierda(n, ArbolGeneral<Tablero> insert(aux));
	  // ultimoinsertado = this->states.hijomasizquierda(n);
	  n->izqda = insertado;
	  ultimoinsertado = n->izqda;
	} else {
	  ultimoinsertado->drcha = insertado;
	  ultimoinsertado = ultimoinsertado->drcha;
	  //this->states.insertar_hermanoderecha(ultimoinsertado, ArbolGeneral<Tablero> insert(aux));
	}

	generaArbolEstados(prof, currentProf+1, ultimoinsertado);
      }
    } //for
  }//if
}


Tablero& Conecta4::siguienteMovimiento(){
  /*
    Nuestro arbol de estados siempre tendra en su raiz el estado
    actual del tablero, de modo que solo tenemos que evaluar los nodos
    que nos indique la profundidad de nuestra heuristica, generar los que falten
    y al salir del metodo actualizar la raiz de nuestro arbol
  */
  int prof = 0;
  int mejorValoracionNodo = -1;
  Tablero mejor; //Presenta el mejor movimiento encontrado

  ArbolGeneral<Tablero>::preorden_iterador it = this->states.beginpreorden();
  //Esto no se paralelizarlo
  for (it; it != this->states.endpreorden() && prof != this->profundidad; ++it) {
    if(it.hermano() == 0){
      prof++;
    }
    int val = evalua((*it)); //Depende de la heuristica varias
			     //llamadas pueden ser muy lentas asi que
			     //almacenamos el valor para usarlo
			     //siempre
    if(val > mejorValoracionNodo){
      mejorValoracionNodo = val;
      mejor = *it;
    }
    
  }

  return mejor;
  
}


//--------------------------------------------------------------------------------
//Funciones de ayda que no pertenecen a la clase
//--------------------------------------------------------------------------------

int get3Horizontales(Tablero& t, int turno){
  vector<vector<int> > tablero = t.GetTablero();    
  int ntreses;

  for (unsigned int i = 0; i < tablero.size()-2; ++i) {
    for (int j; i < tablero.at(i).size(); ++j) {

      if(tablero[i][j] == turno && tablero[i+1][j] == turno && tablero[i+2][j] == turno)
	ntreses++;
      //lleva if else if por que los doses no se suman si son treses
	
    }
    
  }

  return ntreses;
}

int get2Horizontales(Tablero& t, int turno){
  vector<vector<int> > tablero = t.GetTablero();
  int ndoses;
  for (unsigned int i = 0; i < tablero.size()-1; ++i) {
    for (int j; i < tablero.at(i).size(); ++j) {
      if(tablero[i][j] == turno && tablero[i+1][j] == turno)
	ndoses++;
    }
  }

  return ndoses;
}
    

int get2Verticales(Tablero& t, int turno){
  vector<vector<int> > tablero = t.GetTablero();
  int ndoses;

  for (unsigned int i = 0; i < tablero.size(); ++i) {
    for (int j; i < tablero.at(i).size()-1; ++j) {
      //lleva if else if por que los doses no se suman si son treses
      if(tablero[i][j] == turno && tablero[i][j+1] == turno)
	  ndoses++;
    }
  }

  return ndoses;
}

int get3Verticales(Tablero& t, int turno){
  vector<vector<int> > tablero = t.GetTablero();
  int ntreses;
  for (unsigned int i = 0; i < tablero.size(); ++i) {
    for (int j; i < tablero.at(i).size()-2; ++j) {
      if(tablero[i][j] == turno && tablero[i][j+1] == turno && tablero[i][j+2] == turno)
	ntreses++;
    }
  }

  return ntreses;
}
