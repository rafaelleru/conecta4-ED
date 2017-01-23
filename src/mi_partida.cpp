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
 * @brief Captura el caracter pulsado por teclado (sin necesidad de pulsar, a continuación, Enter).
 * @return: Caracter pulsado (char).
 */
char getch () {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}

/******************************************************************************/
/**
 * @brief Implementa el desarrollo de una partida de Conecta 4 sobre un tablero 5x7, pidiendo por teclado los movimientos de ambos jugadores según turno.
 * @return : Identificador (int) del jugador que gana la partida (1 o 2).
 */
int jugar_partida() {
  Tablero tablero(4, 4);      //Tablero 5x7
  Mando mando(tablero);       //Mando para controlar E/S de tablero
  JugadorAuto uno(1, 1);
  JugadorAuto dos(2, 1);    
  int i = 0;
  int quienGana = 0;
  char h;
  tablero.cambiarTurno();
  while(quienGana == 0){
    tablero.cambiarTurno();
    ArbolGeneral<Tablero> states(tablero);
    if(i%2 == 0){
      tablero = uno.getNextBestMove(states);
    }else{
      tablero = dos.getNextBestMove(states);
    }

    cout << "Juego: " << endl;
    cout << tablero;
    ++i;
    quienGana = tablero.quienGana();
  }
  return tablero.quienGana();
}

int humano_vs_player(int f, int c, int turno){
  Tablero t(f,c);
  int quienGana = 0;
  int i = 0;
  Mando mando(t);       //Mando para controlar E/S de tablero
  cout << "antes de los while" << endl;
  if(turno == 1){
    cout << "Juega primero el brother the human" << endl;
    JugadorAuto ja(2, 7);
    while(quienGana == 0){
      ArbolGeneral<Tablero> states(t);
      if(i%2 == 0){
	c = getch();       // Capturamos la tecla pulsada.
	cout << "La tecla es: " << c << endl;
	while(t.GetTurno() == 1 && quienGana == 0) {
	  //system("clear");
	  mando.actualizarJuego(c, t);  // actualiza tablero según comando c 
	  imprimeTablero(t, mando);     // muestra tablero y mando en pantalla
	  quienGana = t.quienGana();    // hay ganador?
	}
	++i;
      }else{
	cout << "Juego yo que soy la polla" << endl;
	t = ja.getNextBestMove(states);
	//system("clear");
	cout << t;
	quienGana = t.quienGana();
	++i;
      }//else
    }//while
  }else{ //Turno 2
    JugadorAuto ja(1, 7);
    while(quienGana == 0){
      ArbolGeneral<Tablero> states(t);
      if(i%2 == 0){//juega jugador automatico
	t = ja.getNextBestMove(states);
	cout << t;
	quienGana = t.quienGana();
      }else{
	c = getch();       // Capturamos la tecla pulsada.    
	if(c != Mando::KB_ESCAPE && quienGana == 0) {
	  //system("clear");
	  mando.actualizarJuego(c, t);  // actualiza tablero según comando c 
	  imprimeTablero(t, mando);     // muestra tablero y mando en pantalla
	  quienGana = t.quienGana();    // hay ganador?
	}
      }
      ++i;
    }
  }

  return quienGana;
  
}

int main(int argc, char *argv[]){
  if(argc == 4){ //cambiar por 4 cuando haya varias heuristicas.
    int ganador = humano_vs_player(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));//jugar_partida();
    cout << "Ha ganado el jugador " << ganador << endl;
  }else{
  
    int ganador = jugar_partida();
    cout << "Ha ganado el jugador " << ganador << endl;
  }
}  

