SRC = src
INC = include
OBJ = obj
LIB = lib
BIN = bin
CXX = g++
AR = ar rvs		
AR_MACOSX = libtool -static -o  
CPPFLAGS = -Wall -g  -I$(INC) -c



all: $(BIN)/conecta4 $(BIN)/arboltablero_test $(BIN)/mipartida
mipartida: $(BIN)/mipartida
# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile

# ************ Compilación de módulos ************
$(BIN)/arboltablero_test: $(OBJ)/arboltablero_test.o $(LIB)/libtablero.a
	$(CXX) -o $(BIN)/arboltablero_test $(OBJ)/arboltablero_test.o -I$(INC) -L$(LIB) -ltablero

$(BIN)/conecta4: $(OBJ)/conecta4.o $(LIB)/libtablero.a $(LIB)/libmando.a
	$(CXX) -o $(BIN)/conecta4 $(OBJ)/conecta4.o -I$(INC) -L$(LIB) -ltablero -lmando

$(OBJ)/conecta4.o: $(SRC)/conecta4.cpp
	$(CXX) $(CPPFLAGS)  -o $(OBJ)/conecta4.o $(SRC)/conecta4.cpp -I$(INC)

$(LIB)/libtablero.a: $(OBJ)/tablero.o
	$(AR) $(LIB)/libtablero.a $(OBJ)/tablero.o

$(LIB)/libmando.a: $(OBJ)/mando.o
	$(AR)  $(LIB)/libmando.a $(OBJ)/mando.o

$(OBJ)/tablero.o: $(SRC)/tablero.cpp $(INC)/tablero.h
	$(CXX) $(CPPFLAGS)  -o $(OBJ)/tablero.o $(SRC)/tablero.cpp -I$(INC)

$(OBJ)/arboltablero_test.o: $(SRC)/arboltablero_test.cpp $(INC)/tablero.h
	$(CXX) $(CPPFLAGS)  -o $(OBJ)/arboltablero_test.o $(SRC)/arboltablero_test.cpp -I$(INC)

$(OBJ)/mando.o: $(SRC)/mando.cpp $(INC)/mando.h $(INC)/tablero.h
	$(CXX) $(CPPFLAGS)  -o $(OBJ)/mando.o $(SRC)/mando.cpp -I$(INC)

#******************** Añadido por nosotros ********************
$(BIN)/mipartida: $(OBJ)/mipartida.o $(LIB)/libtablero.a $(LIB)/libmando.a
	$(CXX) -o $(BIN)/mipartida $(OBJ)/mipartida.o $(OBJ)/JugadorAuto.o -I$(INC) -L$(LIB) -ltablero -lmando

$(OBJ)/mipartida.o: $(SRC)/mi_partida.cpp $(OBJ)/JugadorAuto.o
	$(CXX) $(CPPFLAGS)  -o $(OBJ)/mipartida.o $(SRC)/mi_partida.cpp $(OBJ)/JugadorAuto.o -I$(INC)

$(OBJ)/Conecta4.o: $(SRC)/Conecta4.cpp
	echo "Creando Conecta4.o"
	$(CXX) $(CPPFLAGS)  -o $(OBJ)/Conecta4.o $(SRC)/Conecta4.cpp -I$(INC)

$(OBJ)/JugadorAuto.o: $(SRC)/JugadorAuto.cpp
	echo "Creando jugador automatico"
	$(CXX) $(CPPFLAGS) -o $(OBJ)/JugadorAuto.o $(SRC)/JugadorAuto.cpp -I$(INC)

# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(LIB)/* $(SRC)/*~ $(INC)/*~ ./*~

mrproper : clean
	-rm $(BIN)/* doc/html/*
