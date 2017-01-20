#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <termio.h>     // Linux/Windows users
//#include <termios.h>    // Mac OSX users

#include "ArbolGeneral.h"
#include "tablero.h"
#include "mando.h"
#include "Conecta4.h"
#include "JugadorAuto.h"

using namespace std;

/******************************************************************************/
/**
 * @brief Imprime en pantalla el tablero completo, con el mando y el jugador.
 * @param t : Tablero que se va a imprimir.
 * @param m : Mando indicando la posición del jugador.
 */
void imprimeTablero(Tablero & t, Mando & m){
    cout << m.GetJugador() << endl;
    cout << t ;
    cout << m.GetBase() << endl;
    cout << m.GetMando() << endl;
}

void printTableo(Tablero &t){
  vector<vector<int> >casillas = t.GetTablero();
  for (int i; i < casillas.size(); ++i) {
    for (int j; j < casillas[i].size(); ++j) {
      cout << casillas[i][j] << " ";
    }
    cout << endl;
  }
    
  }

/******************************************************************************/
/**
 * @brief Implementa el desarrollo de una partida de Conecta 4 sobre un tablero 5x7, pidiendo por teclado los movimientos de ambos jugadores según turno.
 * @return : Identificador (int) del jugador que gana la partida (1 o 2).
 */
int jugar_partida() {
  Tablero tablero(4,4);      //Tablero 5x7
  Mando mando(tablero);       //Mando para controlar E/S de tablero
  JugadorAuto uno(1, 5);
  JugadorAuto dos(2, 5);    
  int i = 0;
  int quienGana = 0;

  while(quienGana == 0){
    ArbolGeneral<Tablero> states(tablero);
    if(i%2 == 0){
      tablero = uno.getNextBestMove(states);
      cout << tablero;
    }else{
      cout << "Juega 2" << endl;
      tablero = dos.getNextBestMove(states);
    }

    ++i;
    quienGana = tablero.quienGana();
  }
  return tablero.quienGana();
}

int main(int argc, char *argv[]){

  int ganador = jugar_partida();
  cout << "Ha ganado el jugador " << ganador << endl;
}  
