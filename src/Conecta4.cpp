#include "Conecta4.h"

using namespace std;

int Conecta4::evalua(Conecta4::tritupla& t){
  Tablero tab = t.t;
  t.puntuacion = getHorizontales(t.t) + getVerticales(t.t) + getDiagonales(t.t);
  return 10; //Cambiar aqui
}

void generaArbolEstados(int currentProf = 0, int prof = 2, ArbolGeneral<Tablero> t){
  ArbolGeneral<Tablero>::nodo raiz = generados.getRaiz();
  int nCol = t.getColumnas(); //Asignandolo aqui ahorramos multiples llamadas en el for.

  //1ª version muy simple para generar el tablero.
  //quiza se pueda paralelizar con posix y hebras
  while(currentProf != prof){
    bool hijomasizquierda = false; //Indica si hemos insertado el hijo mas a la izda o no

    for(int i=0; i < nCol; ++i){
      //Si se puede colocar la ficha, se llama recursivamente a generaArbolEstados para
      //que se generen los hijos hasta la prof dada
      if(t.colocarFicha(i)){
	if(!hijomasizquierda){
	  ArbolGeneral<Tablero>::nodo insertado(t);
	  t.insertar_hijomasizquierda(insertado);
	  ultimoInsertado = generados.hijomasizquierda;
	  generaArbolEstados(currentProf+1, prof, ultimoInsertado);
	  hijomasizquierda = true;
	} else{
	  ArbolGeneral<Tablero>::nodo insertado(t);
	  t.insertar_hermanoderecha(ultimoInsertado, insertado);
	  ultimoInsertado = ultimoInsertado.hermanoderecha();
	  generaArbolEstados(currentProf+1, prof, ultimoInsertado);
	}//else
      }//if(t.colocarFicha(i))
    }//for
  }//while
  
}


Tablero& Conecta4::siguienteMovimiento(ArbolGeneral<Tablero>& t){
  



//--------------------------------------------------------------------------------
//Funciones de ayda que no pertenecen a la clase
//--------------------------------------------------------------------------------

int getHorizontales(Tablero& t){
  vector<vector<int> > repr = t.getTablero();
}
