/*
 * KVMachine.h
 *
 *  Created on: Nov 21, 2013
 *      Author: antonio
 */

#ifndef KVMACHINE_H_
#define KVMACHINE_H_

#include <iostream>     // std::cout
#include <cmath>        // std::abs
#include <float.h>
#include "IMachine.h"

class KVMachine: public IMachine {
public:
	KVMachine();
	virtual ~KVMachine();

	void addTrainingSet(std::vector<Sample> trainingSet);
	void clearTrainingSet();
	void setParameters();

private:
	std::vector<Sample> C_trainingSet;
	int C_classifySuccesses;
};

#endif /* KVMACHINE_H_ */
