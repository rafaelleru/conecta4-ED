#include "Conecta4.h"

using namespace std;

int Conecta4::evalua(Tablero& t){

  return 10;
}

void generaArbolEstados(int currentProf = 0, int prof = 2, ArbolGeneral<Tablero>& t){
  ArbolGeneral<Tablero>::Nodo raiz = /*generados*/t.getRaiz();
  int nCol = t.getColumnas(); //Asignandolo aqui ahorramos multiples llamadas en el for.
  Nodo  ultimoInsertado;
  //1ª version muy simple para generar el tablero.
  //quiza se pueda paralelizar con posix y hebras
  while(currentProf != prof){
    bool hijomasizquierda = false; //Indica si hemos insertado el hijo mas a la izda o no

    for(int i=0; i < nCol; ++i){
      //Si se puede colocar la ficha, se llama recursivamente a generaArbolEstados para
      //que se generen los hijos hasta la prof dada
      if(t.colocarFicha(i)){
	if(!hijomasizquierda){
	  ArbolGeneral<Tablero>::Nodo insertado(t);
	  t.insertar_hijomasizquierda(insertado);
	  ultimoInsertado = t.hijomasizquierda;
	  generaArbolEstados(currentProf+1, prof, ultimoInsertado);
	  hijomasizquierda = true;
	} else{
	  ArbolGeneral<Tablero>::Nodo insertado(t);
	  t.insertar_hermanoderecha(ultimoInsertado, insertado);
	  ultimoInsertado = ultimoInsertado.hermanoderecha();
	  generaArbolEstados(currentProf+1, prof, ultimoInsertado);
	}//else
      }//if(t.colocarFicha(i))
    }//for
  }//while
  
}


Tablero& Conecta4::siguienteMovimiento(ArbolGeneral<Tablero>& t){
  ArbolGeneral<Tablero>::Nodo raiz = t.getRaiz();
  int mejor;
  Tablero bestMove;

  ArbolGeneral<Tablero>::preorden_iterador it = t.beginpreorden();

  for(it; it != t.endpreorden(); ++it){
    //Hay qe controlar la profundidad
    if((*it).quienGana() == this->turno){
      return (*it);
    }
    if(evalua(*it) > mejor){
      mejor = evalua(*it);
      bestMove = (*it);
    }


    return bestMove; 
  }
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
