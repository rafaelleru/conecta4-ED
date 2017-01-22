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
  bool izda = false;
  
  if(cd != tope){
    for (int i = 0; i < columnas; ++i) {
      Tablero t(aux->etiqueta);
      if(t.colocarFicha(i)){
	if(!izda){
	  ArbolGeneral<Tablero> nuevoarbol(t);
	  n.insertar_hijomasizquierda(li, nuevoarbol);
	  li = li->izqda;
	  izda = true;
	}else{ //ficha en otra col
	  ArbolGeneral<Tablero> nuevoarbol(t);
	  n.insertar_hermanoderecha(li, nuevoarbol);
	  li = li->drcha;
	}

	li->etiqueta.cambiarTurno();
	cd++;
	generaArbolEstados(n, cd, li);
	cd--;

      }
    }
  }

  return newTree;
}

Tablero& JugadorAuto::getNextBestMove(ArbolGeneral<Tablero>& t, int currentDeep){
  //Generamos los estados a explorar
  ArbolGeneral<Tablero>::Nodo raiz = t.raiz();
  this->generaArbolEstados(t, 0, raiz);

  //Iteradoers para el algoritmo
  ArbolGeneral<Tablero>::preorden_iterador it = t.beginpreorden();
  ArbolGeneral<Tablero>::preorden_iterador mejor = it;
  ArbolGeneral<Tablero>::preorden_iterador end = t.endpreorden();
  ArbolGeneral<Tablero>::preorden_iterador superpadre(t.raiz());
  int mejor_valoracion = 0, val = 0;

  system("clear");
  for (it; it != end; ++it) {
    val = evaluaTablero(*it);

    if(val > mejor_valoracion){
      mejor_valoracion = val;
      mejor = it;
    }
  }

  while(mejor.padre() != superpadre && mejor.padre() != 0)
    mejor = mejor.padre();

  if(mejor == superpadre && mejor.izquierda() != 0)
    mejor = mejor.izquierda();
  return *mejor;
}


//Declaramos los metodos que evaluan las coincidencias en el tablero
int cuenta3Hor(const Tablero &tablero, int player);
int cuenta2Hor(const Tablero &tablero, int player);
int cuenta3Vert(const Tablero &tablero, int player);
int cuenta2Diag(const Tablero &tablero, int player);
int cuenta3Diag(const Tablero &tablero, int player);
int cuentaCuadrados3(const Tablero &tablero, int player);
  
int JugadorAuto::evaluaTablero(Tablero& n){
  int ndosesmios, ntresesmios, ndosesoponente, ntresesoponente;

  if(this->turno == 1){
    int t = 1;
    ndosesmios= cuenta2Hor(n, t) + cuenta2Hor(n, t);
    ndosesoponente = cuenta2Hor(n, t+1) + cuenta2Hor(n, t+1);
  }else{
    int t = 2;
    ndosesmios=cuenta2Hor(n, t) + cuenta2Hor(n, t);
    ndosesoponente = cuenta2Hor(n, t-1) + cuenta2Hor(n, t-1);
  }		  
  return ndosesmios - ndosesoponente*0.5;
}

  int cuenta3Hor(const Tablero &tablero, int player){
    //cout << "Cuento 3 Horizontal: ";
    vector<vector<int> > t = tablero.GetTablero();
    int coincidencias = 0;

    for (size_t i = 0; i < t.size(); i++) {
      for (size_t j = 0; j < t[i].size() - 2; j++) {
        if (t[i][j] == player && t[i][j+1] == player && t[i][j+2] == player) {
	  coincidencias++;
        }
      }
    }
    //cout << coincidencias << endl;
    return coincidencias;
  }

  int cuenta2Hor(const Tablero &tablero, int player){
    //cout << "Cuento 2 Horizontal: ";
    vector<vector<int> > t = tablero.GetTablero();
    int coincidencias = 0;


    for (size_t i = 0; i < t.size(); i++) {
      for (size_t j = 0; j < t[i].size() - 1; j++) { 
        if (  t[i][j] == player && t[i][j+1] == player) {
        coincidencias++;
        }
      }
    }
    //cout << coincidencias << endl;
    return coincidencias;
  }


 int cuenta3Vert(const Tablero &tablero, int player){
    //cout << "Cuento 3 Vertical: ";
    vector<vector<int> > t = tablero.GetTablero();
    int coincidencias = 0;
    

    for (size_t i = 0; i < t.size()-2; i++) {
      for (size_t j = 0; j < t[i].size(); j++) {
        if (  t[i][j] == player && t[i+1][j] == player
          && t[i+2][j] == player) {
        coincidencias++;
        }
      }
    }
    //cout << coincidencias << endl;
    return coincidencias;
  }

  int cuenta2Vert(const Tablero &tablero, int player){
    //cout << "Cuento 2 Vertical: ";
    vector<vector<int> > t = tablero.GetTablero();
    int coincidencias = 0;
    
    for (size_t i = 0; i < t.size() - 1; i++) {
      for (size_t j = 0; j < t[i].size(); j++) {
        if (  t[i][j] == player && t[i+1][j] == player) {
        coincidencias++;
        }
      }
    }
    //cout << coincidencias << endl;
    return coincidencias;
  }


  //Las diagonales, la movida.


  int cuenta3Diag(const Tablero &tablero, int player){
    //cout << "Cuento 3 Diagonal: ";
    vector<vector<int> > t = tablero.GetTablero();
    int coincidencias = 0;

    for (size_t i = 0; i < t.size() - 2; i++) {
      for (size_t j = 0; j < t[j].size() - 2; j++) {
        if(t[i][j] == player && t[i+1][j+1] == player &&
          t[i+2][i+2] == player)
          coincidencias++;
      }
    }

    //coincidencias pal otro lao
    for (size_t i = 0; i < t.size() - 2; i++) {
      for (size_t j = t[i].size(); j > 2; j--) {
        if(t[i][j] == player && t[i+1][j-1] == player &&
          t[i+2][j-2] == player)
          coincidencias++;
      }
    }
    //cout << coincidencias << endl;
    return coincidencias;
  }

  //cuento los cuadrados de 3 x 3 que hay en el tablero
  //Buscamos los casos en los que el tablero contiene posiciones de fichas 
  //que contengan cosas del tipo:
  //* * * * * * *
  //* * * * * * *
  //* * * * * * *
  //1 1 1 * * * 2
  //1 1 1 * * * 1
  //1 1 1 2 2 * 1
  int cuentaCuadrados3(const Tablero &tablero, int player){
  	//cout << "Cuento los cuadrados de 3 fichas que hay";
    int coincidencias = 0;
    /*
    for (size_t i = 0; i < 4; i++){
    	for (int j = 0; j < 4; j++){
    		for (int k = 0; k < 2; k++){
    			for (int l = 0; l < 2; l++){
    				if(t(i,j) == t(k, l))
    					coincidencias++;
    			}
    		}
    	}
    }
    */
    return coincidencias;
  }

  int cuenta2Diag(const Tablero &tablero, int player){

    vector<vector<int> > t = tablero.GetTablero();
    int coincidencias = 0;
    for (size_t i = 0; i < t.size() - 1; i++) {
      for (size_t j = 0; j < t[i].size() - 1; j++) {
        if(t[i][j] == player && t[i+1][j+1] == player)
          coincidencias++;
      }
    }

    //coincidencias pal otro lao
    for (size_t i = 0; i < t.size() ; i++) {
      for (int j = 0; j > t[i].size() - 1; j++){
        if(t[i][j] == player && t[i+1][j-1] == player)
          coincidencias++;
      }
    }
    //cout << coincidencias << endl;
    return coincidencias;
}
