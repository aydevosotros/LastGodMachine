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

	void loadTrainingSet(std::string filename){
		C_machine->loadTrainingSet(filename);
	}

	void loadTestingSet(std::string filename){
		C_machine->loadTestingSet(filename);
	}

	void loadInput(std::string filename){
		C_machine->loadInput(filename);
	}

	void train(){
		C_machine->train();
	}

	void run(){
		C_machine->run();
	}

	void test(){
		C_machine->test();
	}

	double predict(Sample input){
		return C_machine->predict(input);
	}

	void clearTrainingSet(){
		C_machine->clearTrainingSet();
	}

private:
	IMachine* C_machine;

};

#endif /* GODMACHINE_H_ */
