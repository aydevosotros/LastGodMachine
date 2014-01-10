#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

#include "GodMachine.h"

// Ejecución: lgm machine [parámetros de la máquina]

void loadDataSet(std::string fileName){
	//Algooo
}

int main(int argvc, char *argv[]) {
	GodMachine *machine;

	std::vector<Sample> dataSet;

	int maquinaElegida;
	double lambda;

    // Obtengo parametros e inicializo
    if(argvc > 1){
    	int machineType = atoi(argv[2]); // Tipo de máquina

    	switch(machineType){
    	case 0: // KVecinos
    		machine = new GodMachine(KVecinos);
    		break;
    	case 1: // Logistic Regression
    		machine = new GodMachine(LogisticRegression);
    		break;
    	case 2: // Neural Network
			machine = new GodMachine(NeuralNetwork);
			break;
    	case 3: // SVM
    		machine = new GodMachine(SVM);
    		break;
    	default: // Por defecto, LogisticRegression
    		machine = new GodMachine(LogisticRegression);
    		break;
    	}

    	loadDataSet("hardCoded.txt"); //Carga los datos, donde quiera que estén, en el vector de samples

    	machine->addTrainingSet(dataSet);

    	//Y seguiríamos

    } else{
    	// Error de "Nº de parámetros incorrecto, pero ¿cómo?"
    }
}

