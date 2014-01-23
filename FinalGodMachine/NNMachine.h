/*
 * NNMachine.h
 *
 *  Created on: Jan 16, 2014
 *      Author: antonio
 */

#ifndef NNMACHINE_H_
#define NNMACHINE_H_

#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
//#include <lbfgs.h>
#include "armadillo"
#include "Utils.h"

#include "IMachine.h"

typedef arma::mat M2;

class NNMachine: public IMachine {
public:
	NNMachine();
	virtual ~NNMachine();

	void setParameters(char *argv[]);
	void loadTrainingSet(std::string filename);
	void loadTestingSet(std::string filename);
	void loadInput(std::string filename);
	void train();
	void run();
	void test();
	double predict(Sample input);
	void clearTrainingSet();

private:
	int L; //Número de capas
	int nFeatures;
	double lambda;
	std::vector<int> s_l; //número de nodos por capa
	std::vector<Sample> trainingSet; //Conjunto de samples para el entrenamiento
	std::vector<arma::mat> thetas; //L-1 matrices
	std::vector<arma::Col<double> > a;
	std::vector<arma::mat> upperDelta;
	std::vector<arma::mat> D;
	std::vector<double> y;

	void forwardPropagate(Sample s);
	void backPropagate(Sample s);

	void trainByGradient(int iter, double alpha);

	void initTraining();
	void initTrainingXNOR();
	void initRandomThetas();
	double sigmoid(double z);
	void gradChecking();
	double cost();
};

#endif /* NNMACHINE_H_ */
