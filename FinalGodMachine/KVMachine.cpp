/*
 * KVMachine.cpp
 *
 *  Created on: Nov 21, 2013
 *      Author: antonio
 */

#include "KVMachine.h"

KVMachine::KVMachine() {
	C_classifySuccesses = 0;
}

KVMachine::~KVMachine() {

}

void KVMachine::addTrainingSet(std::vector<Sample> trainingSet) {
	C_trainingSet = trainingSet;
}

void KVMachine::clearTrainingSet() {
	C_trainingSet.clear();
	C_classifySuccesses = 0;
}

void KVMachine::setParameters() {
}

//Este no pero alguno parecido habrá que hacer
//bool KVMachine::isReadyToCross() {
//	return classifySuccesses > 50;
//}

//Depende de la Sample, no se toca
//void KVMachine::classifySample(Sample sample) {
////	int nearest = 0;
////	double nearestDistance = DBL_MAX;
////	for(int i = 0; i < trainingSet.size(); i++){
////		double tmp = std::abs((sample.input[0] - trainingSet[i].input[0]));
////		if (tmp < nearestDistance){
////			nearestDistance = tmp;
////			nearest = i;
////		}
////	}
////	if (trainingSet[nearest].burn == sample.burn){
////		classifySuccesses++;
////	}
//}

//Mejor que devolviera un entero, es el prinicipal
//bool KVMachine::isDoorOnFire(double input[]) {
//	int nearest = 0;
//	double nearestDistance = DBL_MAX;
//	for(int i = 0; i < trainingSet.size(); i++){
//		double tmp = std::abs((input[0] - trainingSet[i].input[0]));
//		if (tmp < nearestDistance){
//			nearestDistance = tmp;
//			nearest = i;
//		}
//	}
////		std::cout << "El valor más cercano a " << input << " es " << trainingSet[nearest].input[0] << " y la puerta arde: " << trainingSet[nearest].burn << std::endl;
//
//	return trainingSet[nearest].burn;
//}
