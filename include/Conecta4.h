#ifndef __Conecta_4__
#define __Conecta_4__

#include "ArbolGeneral.h"
#include "tablero.h"

class Conecta4{
 public:
  //Almacena si un estado ha sido evaluado ya con la heuristica, su puntuacion y el tablero en si;
  struct tritupla{
    int puntuacion;
    bool eval;
    Tablero t;
  }
  
  ArbolGeneral<tritupla> states;
  int profundidad;
  
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
  int evalua(tritupla& t);
}
#endif
