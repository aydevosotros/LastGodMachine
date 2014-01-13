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
	void loadTrainingSet(std::string filename);
	void loadTestingSet(std::string filename);
	void loadInput(std::string filename);
	void train();
	void run();
	void test();
	void predict();
	void clearTrainingSet();

private:
	//ATRIBUTOS

	//Atributos pasados por parámetro
	double C_lambda;
	int C_executionMode;
	std::string C_trainingFile;
	std::string C_testingFile;
	std::string C_thetasFile;
	std::string C_inputFile;

	//Atributos cargados desde archivo
	std::vector<Sample> C_trainingSet;
	std::vector<Sample> C_testingSet;
	std::vector<double> C_theta;
	Sample C_input;

	//Usados en el cálculo
	int C_classifySuccesses;
	int C_nFeatures;
	std::vector<std::vector<double> > C_X; //esto no es una matriz BIdimensional diría
	std::vector<double> C_y; //Son doubles pero los valores son enteros, no?

	//Ni zorra
	int iterTrain;
	double alphaTrain;
	int trainType;

	//FUNCIONES

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

	void loadThetas(std::string filename);

};

#endif /* LRMACHINE_H_ */
