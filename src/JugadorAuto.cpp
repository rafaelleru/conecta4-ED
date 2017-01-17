#include "JugadorAuto.h"

using namespace std;

ArbolGeneral<Tablero>::Nodo& JugadorAuto::getNextBestMove(const ArbolGeneral<Tablero>& t, int deep, int currentDeep){

  ArbolGeneral<Tablero>::Nodo best_node;
    int value_node = 0;
    int best_value_node = -1;

    if(currentDeep <= deep){

      ArbolGeneral<Tablero>::preorden_iterador it = t.beginpreorden();
      for(it; it != t.endpreorden() && currentDeep != deep; ++it){

	if(it.hermano() == 0)
	  ++deep;

	value_node = evaluaTablero(*it);

	if(value_node > best_value_node){
	  best_value_node = value_node;
	  best_node = //it a nodo;
	}
      }//for
    }

    for(deep; deep > currentDeep; --deep)
      best_node = best_node->padre;

    return best_node;
}//metodo


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

int JugadorAuto::evaluaTablero(ArbolGeneral<Tablero>::Nodo& n){
  return  get2Verticales(n->etiqueta, this->turno) + get3Verticales(n->etiqueta, this->turno) + get2Horizontales(n->etiqueta, this->turno) + get3Horizontales(n->etiqueta, this->turno);
}//metodo

