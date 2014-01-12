#ifndef GODMACHINE_H_
#define GODMACHINE_H_

#include <iostream>
#include <cmath>
#include <vector>
#include <float.h>

#include "IMachine.h"
#include "LRMachine.h"

enum Machine {LogisticRegression, NeuralNetwork, SVM};

//Falta
class GodMachine {
public:
	GodMachine(){
		C_machine = new LRMachine();
	}

	//Falta
	GodMachine(Machine m){
		switch(m){
			case LogisticRegression:
				C_machine = new LRMachine();
				break;
			//Faltan por añadir los casos de la SVM y de la NN
		}
	}

	virtual ~GodMachine(){}

	void setParameters(char *argv[]){
		C_machine->setParameters(argv);
	}

	void addTrainingSet(std::vector<Sample> trainingSet){
		C_machine->addTrainingSet(trainingSet);
	}

	void train(){
		C_machine->train();
	}

	void predict(Sample input){
		C_machine->predict(input);
	}

	void clearTrainingSet(){
		C_machine->clearTrainingSet();
	}

private:
	IMachine* C_machine;

};

#endif /* GODMACHINE_H_ */
