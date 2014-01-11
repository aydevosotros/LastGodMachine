#ifndef LRMACHINE_H_
#define LRMACHINE_H_

#include <cmath>
#include <iostream>
#include <vector>
#include <lbfgs.h>
#include "armadillo"

#include "IMachine.h"

// Implementar Precision and Recall

class LRMachine : public IMachine {
public:
	LRMachine();
	virtual ~LRMachine();

	void setParameters(char *argv[]);
	void addTrainingSet(std::vector<Sample> trainingSet);
	void train();
	void addInput(Sample input);
	void predict();
	void clearTrainingSet();

private:
	double C_lambda;
	std::vector<Sample> C_trainingSet;
	int C_classifySuccesses;
	int nFeatures;
	std::vector<std::vector<double> > X;
	std::vector<double> y;
	std::vector<double> theta;
	int iterTrain;
	double alphaTrain;
	int trainType;

	// Internal functions
	double sigmoid(double z);
	double cost(std::vector<double> theta, std::vector<std::vector<double> > X, std::vector<double> y);
	void grad(std::vector<double> tetha, std::vector<std::vector<double> > X, std::vector<double> y, std::vector<double> grad);
	void trainByGradient(int iter, double alpha);
	void trainByGradientAdvanced(int iter, double alpha);
	void trainByNormalEcuation();

	// Auxiliar functions
	void fillX();
	void fillTheta();
	void fillY();

};

#endif /* LRMACHINE_H_ */
