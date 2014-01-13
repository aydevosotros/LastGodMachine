#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

#include "GodMachine.h"
#include "Sample.h"

/* Ejecución: lgm machine [parámetros de la máquina]
 *
 * Parámetros de la máquina:
 * 0 - Logistic Regression:
 * 		1. Modo de ejecución
 * 			0 para el testing
 * 			1 para la ejecución
 * 		2. Dependiendo del parametro anterior
 * 			0 - nombre del fichero training
 * 				nombre del fichero test
 * 			1 - nombre del fichero del input
 * 		3. Lambda
*/

int main(int argvc, char *argv[]) {
	GodMachine *machine;

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

    	machine->run();
//
//    	loadDataSet("hardCodedDataSet.txt"); //Carga los datos, donde quiera que estén, en el vector de samples
//
//    	loadInput("hardCodedInput.txt"); //Carga la prueba que queremos predecir
//
//    	machine->addTrainingSet(dataSet);
//
//    	machine->train();
//
//    	machine->predict(input);
//
//    	//Y ahora qué?

//		machine->clearTrainingSet();
    }
}
