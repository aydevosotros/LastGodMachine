/*
 * main.cpp
 *
 *  Created on: Jan 10, 2014
 *      Author: antonio
 */

#include "GodMachine.h"
#include <stdlib.h>
#include <iostream>
#include <vector>

int
main(int argvc, char *argv[]) {
    // Create a new game starting at level 0, and staying at the same level all the time.
    // Use GDM_LEVELUP for increasing level of difficulty
	GodMachine *machine;
    int minDoorsToNextLevel = 100; // Esto también se debería de pasar por parámetro o algo


	 int nivelDeJuego;
	 int maquinaElegida;
	 double lambda;




    // Obtengo parametros e inicializo
    if(argvc > 1){ // Para una ejecución rápida... más o menos: firebitch initLevel machine [los parámetros que puedan requerir cada máquina]
    	int level = atoi(argv[1]); // Nivel inicial del juego
    	int machineType = atoi(argv[2]); // Tipo de máquina
    	switch(machineType){
    	case 0: // KVecinos o lo que sea eso
    		machine = new GodMachine(KVecinos);
    		break;
    	case 1: // Logistic regression
    		machine = new GodMachine(LogisticRegresion);

    		break;
    	case 2: // Neural Network
			machine = new GodMachine(neuralNetwork);

			break;
    	case 3: // SVM
    		machine = new GodMachine(SVM);
    		break;
    	default: // Por defecto
    		machine = new GodMachine(LogisticRegresion);
    		break;
    	}

    } else{ // Aquí lo ideal sería es que si no se pasan parámetros se inicien parámetros por defecto y salga un menú con las opciones


    	 std::cout << "Seleccionar el nivel inicial del juego(0-9): ";
    	 std::cin >> nivelDeJuego;

    	 system("cls");

    	 std::cout << "1.KVecinos " << std::endl;
    	 std::cout << "2.LogisticRegresion " << std::endl;
    	 std::cout << "3.Neural network " << std::endl;
    	 std::cout << "4.Support vector machines " << std::endl;
    	 std::cout << "Selecciona la maquina: ";
    	 std::cin >> maquinaElegida;

    	 system("cls");

    	 std::cout << "Introduce el lambda: ";
    	 std::cin >> lambda; //es un double?

    	 system("cls");

    	switch(maquinaElegida){
    	case 1: // KVecinos
    		machine = new GodMachine(KVecinos);
    	break;
    	case 2: //LogisticRegresion
    		machine = new GodMachine(LogisticRegresion);
    		machine->pedirParametros();
    	break;
    	case 3: // Neural network
        	machine = new GodMachine(neuralNetwork);
        	machine->pedirParametros();
    	break;
    	case 4: //Support vector machines
    		std::cout << "Tico tico tico tico tico tico tico tico tico";
    	break;
    	}
    }
}

