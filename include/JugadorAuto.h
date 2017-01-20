#ifndef __JugadorAuto__
#define __JugadorAuto__

#include "Conecta4.h"

using namespace std;

class JugadorAuto{
 private:
  int turno;
  int tope;

  /**
   *  \brief obtiene la heuristica para un nodo del arbol de estados dado
   *
   *  \param n Nodo el nodo que continee el tablero a evaluar
   *  \return punt int el valor obtenido por dicho nodo en base a nuestra heuristica.
   */
  int evaluaTablero(Tablero& n);
  ArbolGeneral<Tablero>& generaArbolEstados(ArbolGeneral<Tablero>& n, int cd, ArbolGeneral<Tablero>::Nodo& li);
 public:

  /**
   *  \brief constructor de jugador, se le pasa el turno y
   *  opcinalmente la profundidad maxima de exploracion que realizara
   *  sobre el arbol de estados del juego
   *
   *  \param turno int el turno en el que juega el jugador 
   *  \param tope el maximo nivel de profundidad que se alcanzara explorando el arbol de estados del juego, por defecto es 4.
   */
  JugadorAuto(int turno, int tope = 4);

  
  /**
   * @brief Devuelve el nodo hijo del nodo raiz en el que está la mejor jugada
   * @param t ArbolGeneral<Tablero> Arbol de estados de los posibles tableros
   * @param deep int Profundidad en la que se va mirar el mejor movimiento
   * @param currentDeep int Profundidad actual en la que está
   * @return best_node Nodo Devuelve el nodo hijo del raiz en la rama del mejor nodo
   */
  Tablero& getNextBestMove(ArbolGeneral<Tablero>& t, int currentDeep = 0);
};


#endif
