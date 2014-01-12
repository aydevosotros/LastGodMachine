#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

#include "GodMachine.h"
#include "Sample.h"

// Ejecución: lgm machine [parámetros de la máquina]

void loadDataSet(std::string fileName){
	//Algooo
}

void loadInput(std::string input){
	//Algooo
}

int main(int argvc, char *argv[]) {
	GodMachine *machine;

	std::vector<Sample> dataSet;
	Sample input;

	int maquinaElegida;
	double lambda;

    // Obtengo parametros e inicializo
    if(argvc > 1){
    	int machineType = atoi(argv[1]); // Tipo de máquina

    	switch(machineType){
    	case 0: // Logistic Regression
    		machine = new GodMachine(LogisticRegression);
    		break;
    	case 1: // Neural Network
			machine = new GodMachine(NeuralNetwork);
			break;
    	case 2: // SVM
    		machine = new GodMachine(SVM);
    		break;
    	default: // Por defecto, LogisticRegression
    		machine = new GodMachine(LogisticRegression);
    		break;
    	}

    	machine->setParameters(argv);

    	loadDataSet("hardCodedDataSet.txt"); //Carga los datos, donde quiera que estén, en el vector de samples

    	loadInput("hardCodedInput.txt"); //Carga la prueba que queremos predecir

    	machine->addTrainingSet(dataSet);

    	machine->train();

    	machine->predict(input);

    	//Y ahora qué?

//		machine->clearTrainingSet();
    } else{
    	std::cout << "Nº de argumentos incorrecto" << std::endl;
    }
}
