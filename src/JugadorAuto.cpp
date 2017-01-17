#include "JugadorAuto.h"

using namespace std;

ArbolGeneral<Tablero>::Nodo& JugadorAuto::getNextBestMove(const ArbolGeneral<tablero>& t, int deep, int currentDeep){

    Nodo best_node;
    int value_node, best_value_node;
    if(currentDeep <= deep){
      ArbolGeneral<Tablero>::preorden_iterador it = t.beginpreorden();
      for(it; it != t.endpreorden() && currentDeep != deep; ++it){
	if(it.hermano() == 0)
	  ++deep;
	value_node = evalua(*it);
	
      }
    }

    return best_node;
  }//Fin metodo

  
};//Fin clase
