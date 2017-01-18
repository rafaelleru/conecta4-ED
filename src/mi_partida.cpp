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

/******************************************************************************/
/**
 * @brief Implementa el desarrollo de una partida de Conecta 4 sobre un tablero 5x7, pidiendo por teclado los movimientos de ambos jugadores según turno.
 * @return : Identificador (int) del jugador que gana la partida (1 o 2).
 */
int jugar_partida() {

    Tablero tablero(5, 7);      //Tablero 5x7
    Mando mando(tablero);       //Mando para controlar E/S de tablero
    Conecta4 conecta(4, tablero);
    JugadorAuto uno(1, 7);
    JugadorAuto dos(2, 7);    
    int i = 0;
    int quienGana = 0;
    Tablero n;
    while(quienGana == 0){
      if(i%2 == 0){ //Juega 1
	n = uno.getNextBestMove(conecta.getStates());
      }else{
	n = dos.getNextBestMove(conecta.getStates());
      }
      
      conecta.actualizarEstado(n);
      system("clear");
      //mando.actualizarJuego(c, tablero);  // actualiza tablero según comando c 
      imprimeTablero(n, mando);     // muestra tablero y mando en pantalla
      quienGana = n.quienGana();    // hay ganador?
    }

    return tablero.quienGana();
}

int main(int argc, char *argv[]){
    int ganador = jugar_partida();
    cout << "Ha ganado el jugador " << ganador << endl;
}  
