#ifndef __Conecta_4__
#define __Conecta_4__

#include "ArbolGeneral.h"
#include "tablero.h"

using namespace std;
class Conecta4{
 private:

  /**
   *   \file Conecta4.h 
   *   \brief  TDA necesario para gestionar una partida de Conecta
   *
   *   Implementa el TDA necesario para
   *   gestionar una partida de Conecta4 entre dos jugadores
   *   automaticos, almacenando para ello un arbol de posibles estados
   *   en el tablero
   *
   * Segun nuestra implementacion esta case deberia diseñarse con el
   * patron de diseño singleton
   *
   */

  /*!< almacena el conjunto de estados de la partida */
  ArbolGeneral<Tablero> states;
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
  Conecta4(int f, int c);

  /**
   *  \brief constructor a partir de un tablero
   *  \param tablero el tablero que sera el nodo raiz de nuestro arbol
   */
  Conecta4(int prof,Tablero& tablero);

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
  void actualizarEstado(Tablero& n);

  /**
   *  \brief devuelve una referencia constante al arbol de estados que almacena Conecta4
   *  \return return const ArbolGeneral<Tablero>& referencia constante al arbol de estados de la partida.
   */
  const ArbolGeneral<Tablero>& getStates();
};
#endif
