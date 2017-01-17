#include "JugadorAuto.h"

using namespace std;

ArbolGeneral<Tablero>::Nodo& JugadorAuto::getNextBestMove(const ArbolGeneral<tablero>& t, int deep, int currentDeep){

    Nodo best_node;
    int value_node = 0;
    int best_value_node = -1;

    if(currentDeep <= deep){

      ArbolGeneral<Tablero>::preorden_iterador it = t.beginpreorden();
      for(it; it != t.endpreorden() && currentDeep != deep; ++it){

	if(it.hermano() == 0)
	  ++deep;

	value_node = evalua(*it);

	if(value_node > best_value_node){
	  best_value_node = value_node;
	  best_node = *it;
	}
      }//for
    }

    for(deep; deep > currentDeep; --deep)
      best_node = best_node->padre;

    return best_node;
}//metodo
