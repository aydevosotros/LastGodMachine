#ifndef GODMACHINE_H_
#define GODMACHINE_H_

#include <iostream>     // std::cout
#include <cmath>        // std::abs
#include <vector>		// std::vector
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

	void addInput(Sample input){
		C_machine->addInput(input);
	}

	void predict(){
		C_machine->predict();
	}

	void clearTrainingSet(){
		C_machine->clearTrainingSet();
	}

private:
	IMachine* C_machine;

};

#endif /* GODMACHINE_H_ */
