#include "JugadorAuto.h"

using namespace std;

JugadorAuto::JugadorAuto(int turno, int tope){
  this->turno = turno;
  this->tope = tope;
}

Tablero& JugadorAuto::getNextBestMove(const ArbolGeneral<Tablero>& t, int deep, int currentDeep){
  Tablero best;
  int value_node = 0;
  int best_value_node = -1;

  ArbolGeneral<Tablero>::preorden_iterador it = t.beginpreorden();

    for(it; it != t.endpreorden() && currentDeep <= this->tope; ++it){

      if(it.hermano() == 0)
	++currentDeep;

      value_node = evaluaTablero(*it);

      if(value_node > best_value_node){
	best_value_node = value_node;
	best = *it;
      }
    }//for

  for(deep; deep > currentDeep; --deep){
    it = it.padre();
  }
    

  return *it;
}//metodo


//--------------------------------------------------------------------------------
//Funciones de ayda que no pertenecen a la clase
//--------------------------------------------------------------------------------

int get3Horizontales(Tablero& t, int turno){
  vector<vector<int> > tablero = t.GetTablero();    
  int ntreses;

  for (unsigned int i = 0; i < tablero.size()-2; ++i) {
    for (int j = 0; i < tablero.at(i).size(); ++j) {

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
    for (int j = 0; i < tablero.at(i).size(); ++j) {
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
    for (int j=0; i < tablero.at(i).size()-1; ++j) {
      //lleva if else if por que los doses no se suman si son treses
      if(tablero[i][j] == turno && tablero[i][j-1] == turno)
	  ndoses++;
    }
  }

  return ndoses;
}

int get3Verticales(Tablero& t, int turno){
  vector<vector<int> > tablero = t.GetTablero();
  int ntreses;
  for (unsigned int i = 0; i < tablero.size(); ++i) {
    for (int j = 0; i < tablero.at(i).size()-2; ++j) {
      if(tablero[i][j] == turno && tablero[i][j+1] == turno && tablero[i][j+2] == turno)
	ntreses++;
    }
  }

  return ntreses;
}

int JugadorAuto::evaluaTablero(Tablero& n){
  //return  get2Verticales(n, this->turno) + get3Verticales(n, this->turno) +
  //get2Horizontales(n, this->turno) + get3Horizontales(n, this->turno);

  return 20;
}//metodo

