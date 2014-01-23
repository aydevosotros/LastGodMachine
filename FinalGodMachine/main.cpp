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
 * 		param1 = Modo de ejecución:
 * 			0 - para el testing
 * 			1 - para la ejecución
 *
 * 		param2 = Dependiendo del parametro anterior:
 * 			param1 = 0 -> 	nombre del fichero training
 * 							nombre del fichero test
 *
 * 			param1 = 1 -> 	nombre del fichero del input
 *
 * 		param3 = Lambda
 *
 * 2 - Support Vector Machine:
 * 		param1 = Modo de ejecución:
 * 			0 - para el testing
 * 			1 - para la ejecución
 *
 * 		param2 = Dependiendo del parametro anterior:
 * 			param1 = 0 -> 	nombre del fichero training
 * 							nombre del fichero test
 *
 * 			param1 = 1 -> 	nombre del fichero del input
 *
 * 		param3 = Margin
 * 			0 - soft
 * 			1 - hard
 *
 * 3 - Linear Regression:
 * 		param1 = Modo de ejecución:
 * 			0 - para el testing
 * 			1 - para la ejecución
 *
 * 		param2 = Dependiendo del parametro anterior:
 * 			param1 = 0 -> 	nombre del fichero training
 * 							nombre del fichero test
 *
 * 			param1 = 1 -> 	nombre del fichero del input
 *
 * 		param3 = trainingType
 * 			1 - Normal
 * 			1 - Gradient
 *
 * 		param3 = 1 ->	param4 = alpha
 *
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
    	case 3: // Linear Regression
    		machine = new GodMachine(LinearRegression);
    		break;
    	default: // Por defecto, Logistic Regression
    		machine = new GodMachine(LogisticRegression);
    		break;
    	}

    	machine->setParameters(argv);

    	machine->run();
    }
}
