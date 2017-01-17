#ifndef __JugadorAuto__
#define __JugadorAuto__

#include "Conecta4.h"

using namespace std;

class JugadorAuto{
 public:
  /**
   * @brief Devuelve el nodo hijo del nodo raiz en el que está la mejor jugada
   * @param t ArbolGeneral<Tablero> Arbol de estados de los posibles tableros
   * @param deep int Profundidad en la que se va mirar el mejor movimiento
   * @param currentDeep int Profundidad actual en la que está
   */
  Nodo& getNextBestMove(const ArbolGeneral<Tablero>& t, int deep, int currentDeep);
};
