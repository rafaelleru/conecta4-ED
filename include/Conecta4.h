#ifndef __Conecta_4__
#define __Conecta_4__

#include "ArbolGeneral.h"
#include "tablero.h"

using namespace std;
class Conecta4{
 public:
  //Almacena si un estado ha sido evaluado ya con la heuristica, su puntuacion y el tablero en si;
  struct tritupla{
    int puntuacion;
    Tablero t;
  };
  //Aquí da fallo porque creo que tritupla al estar definido en Conecta4 no puede ser ArbolGeneral.
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
 private:
  /**
   * @brief crea una partida de Conecta4 vacia;
   * @param p la profundidad hasta la que se explorara el arbol;
   */
  Conecta4(int p);

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
  Tablero& siguienteMovimiento(ArbolGeneral<Tablero>& t);
};
#endif
