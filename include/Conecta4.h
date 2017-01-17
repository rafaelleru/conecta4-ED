#ifndef __Conecta_4__
#define __Conecta_4__

#include "ArbolGeneral.h"
#include "tablero.h"

using namespace std;
class Conecta4{
 private:
  ArbolGeneral<Tablero> states;
  int profundidad;
  int turno;

  /**
   *  \brief genera los futuros estados para una profundida prof a partir del estado del tablero t
   *
   *  \param prof la profundidad que tendran los estados finales del arbol de estado (los nodos hoja)
   *  \param t el tablero a partir del cual se ramifica para los futuros estados
   */
  void generaArbolEstados(int prof, int currentProf, ArbolGeneral<Tablero>::Nodo& n);			  
 public:
  /**
   * @brief crea una partida de Conecta4 vacia;
   * @param p la profundidad hasta la que se explorara el arbol;
   */
  Conecta4(int p, int t);

  /**
   *  \brief devuelve la evaluacion del Tablero contenido en t
   *  \param t tritupla que contiene el tablero a evaluar;
   *  \return puntuacion la puntuacion obtenida para el Tablero que contiene t
   */
  int evalua(Tablero& t);

  /**
   *  \brief obtiene el siguiente mejor movimiento
   *
   *  usamos anchura que garantiza la mejor solución.
   *
   *  \param n representa el estado a partir del cual jugamos
   *  \return tablero quecontiene el siguiente movimiento.
   */
  Tablero& siguienteMovimiento(); //en states siempre estara el tablero actual como nodo raiz

  /**
   *  \brief actualiza el estado actual del tablero de juego
   *
   *  cuando se produce un movimiento por algun jugador el tablero que
   *  se crea debido a ese movimiento pasa a ser el nuevo nodo raiz de
   *  states
   *
   *  \param n el nodo que conformara el nuevo estado raiz de states
   */
  void actualizarEstado(ArbolGeneral<Tablero>::Nodo& n);
};
#endif
