#include "JugadorAuto.h"
#include <vector>

using namespace std;

JugadorAuto::JugadorAuto(int turno, int tope){
  this->turno = turno;
  this->tope = tope;
}

ArbolGeneral<Tablero>& JugadorAuto::generaArbolEstados(ArbolGeneral<Tablero> &n, int cd, ArbolGeneral<Tablero>::Nodo& li){
  static ArbolGeneral<Tablero> newTree(n);
  int columnas = li->etiqueta.GetColumnas();
  ArbolGeneral<Tablero>::Nodo aux = li;

  if(cd != tope){
    for (int i = 0; i < columnas; ++i) {
      Tablero t(aux->etiqueta);
      if(t.colocarFicha(i)){
	if(i == 0){
	  ArbolGeneral<Tablero> nuevoarbol(t);
	  n.insertar_hijomasizquierda(li, nuevoarbol);
	  li = li->izqda;
	}else{ //ficha en otra col
	  ArbolGeneral<Tablero> nuevoarbol(t);
	  n.insertar_hermanoderecha(li, nuevoarbol);
	  li = li->drcha;
	}

      }

      li->etiqueta.cambiarTurno();
      cd++;
      generaArbolEstados(n, cd, li);
      cd--;
    }
  }

  return newTree;
}
// Tablero& JugadorAuto::getNextBestMove(const ArbolGeneral<Tablero>& t, int deep, int currentDeep){
//   //mi propia navegacion en el arbol, en anchura
//   ArbolGeneral<Tablero>::Nodo n = t.raiz();
//   queue<ArbolGeneral<Tablero>::Nodo> to_explore;
//   currentDeep = 0;
//   this->tope = 2;

//   ArbolGeneral<Tablero>::Nodo mejor;
//   int mejorValorado = 100000000000;
//   to_explore.push(n);
//   int i = 1;
//   ArbolGeneral<Tablero>::Nodo nodo_actual;
//   int val;
  
//   while(!to_explore.empty()){
//     nodo_actual = to_explore.front();
//     cout << t.altura(nodo_actual) << "  ";
//     to_explore.pop();
//     val = evaluaTablero(nodo_actual->etiqueta);
//     if(mejorValorado >  val){
//       mejorValorado = val;
//       mejor = nodo_actual;
//     }

//     if(nodo_actual->izqda != 0){
//       nodo_actual= nodo_actual->izqda;
//       to_explore.push(nodo_actual);
    
//       while(nodo_actual->drcha != 0){
// 	nodo_actual = nodo_actual->drcha;
// 	to_explore.push(nodo_actual);
//       }

//       currentDeep++;

//     }
//   }
//   cout << "antes del return" << endl;
//   return mejor->etiqueta;

// }
Tablero& JugadorAuto::getNextBestMove(ArbolGeneral<Tablero>& t, int currentDeep){
  ArbolGeneral<Tablero>::Nodo raiz = t.raiz();
  this->generaArbolEstados(t, 0, raiz);
  ArbolGeneral<Tablero>::preorden_iterador it = t.beginpreorden();
  ArbolGeneral<Tablero>::preorden_iterador mejor;
  ArbolGeneral<Tablero>::preorden_iterador end = t.endpreorden();
  ArbolGeneral<Tablero>::preorden_iterador superpadre(t.raiz());
  int mejor_valoracion = 0;
  
  for (it; it != end; ++it) {
    int valoracion_actual = evaluaTablero(*it);
    if(valoracion_actual > mejor_valoracion){
      mejor_valoracion = valoracion_actual;
      mejor = it;
    }
  }

  vector<ArbolGeneral<Tablero>::preorden_iterador> hijossuperpadre;
  superpadre = superpadre.izquierda();
  hijossuperpadre.push_back(superpadre);
  while(superpadre.hermano() != 0){
    hijossuperpadre.push_back(superpadre);
    superpadre = superpadre.hermano();
  }

  while(mejor.padre() != 0){
    mejor = mejor.padre();
    for(vector<ArbolGeneral<Tablero>::preorden_iterador>::iterator vt = hijossuperpadre.begin(); vt != hijossuperpadre.end(); ++vt){
      if(mejor == *vt)
	return *mejor;
    }
  }
}
  
//--------------------------------------------------------------------------------
//Funciones de ayda que no pertenecen a la clase
//--------------------------------------------------------------------------------

int get3Horizontales(Tablero& t, int turno){
  vector<vector<int> > tablero = t.GetTablero();    
  int ntreses = 0;

  for(int i = 0; i < tablero.size()-2; ++i) {
    for (int j = 0; j < tablero.at(i).size(); ++j) {
      if(tablero[i][j] == turno && tablero[i+1][j] == turno && tablero[i+2][j] == turno)
	ntreses++;
    }
  }
  cout << "ntreses: " << ntreses << endl;
  return ntreses;
}

int get2Horizontales(Tablero& t, int turno){
  vector<vector<int> > tablero = t.GetTablero();
  int ndoses = 0;
  for(int i = 0; i < tablero.size()-1; ++i) {
    for (int j = 0; j < tablero.at(i).size(); ++j) {
      if(tablero[i][j] == turno && tablero[i+1][j] == turno)
	ndoses++;
    }
  }

  return ndoses;
}
    

int get2Verticales(Tablero& t, int turno){
  vector<vector<int> > tablero = t.GetTablero();
  int ndoses = 0;
  for (int i = 0; i < tablero.size(); ++i) {
    for (int j=0; j < tablero.at(i).size()-1; ++j) {
      if(tablero[i][j] == turno && tablero[i][j+1] == turno){
	ndoses++;
      }
    }
  }
  return ndoses;
}

int get3Verticales(Tablero& t, int turno){
  vector<vector<int> > tablero = t.GetTablero();
  int ntreses = 0;
  for (unsigned int i = 0; i < tablero.size(); ++i) {
    for (int j = 0; i < tablero.at(i).size()-2; ++j) {
      if(tablero[i][j] == turno && tablero[i][j+1] == turno && tablero[i][j+2] == turno)
	ntreses++;
    }
  }

  return ntreses;
}

int JugadorAuto::evaluaTablero(Tablero& n){
  if(this->turno == 1){
    return  get2Verticales(n, this->turno);
  }else{
    return get2Horizontales(n, this->turno);
  }// + get3Verticales(n, this->turno);    //  get2Horizontales(n, this->turno) + get3Horizontales(n, this->turno); 
}

