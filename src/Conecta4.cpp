#include "Conecta4.h"

using namespace std;

int Conecta4::evalua(Conecta4::tritupla& t){
  Tablero tab = t.t;
  t.puntuacion = getHorizontales(t.t) + getVerticales(t.t) + getDiagonales(t.t);
  return t.puntuacion;
}





//--------------------------------------------------------------------------------
//Funciones de ayda que no pertenecen a la clase
//--------------------------------------------------------------------------------

int getHorizontales(Tablero& t){
  vector<vector<int> > repr = t.getTablero();
}
