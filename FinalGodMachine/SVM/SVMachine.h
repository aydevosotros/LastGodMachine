#ifndef SVMACHINE_H_
#define SVMACHINE_H_

#include <iostream>
#include <vector>
#include <CGAL/MP_Float.h>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>

#include "armadillo"

#include "../IMachine.h"
#include "../Utils.h"
#include "IKernel.h"
#include "LinearKernel.h"
#include "PolynomialKernel.h"
#include "RBFKernel.h"

typedef std::vector<Sample> VSample;
typedef CGAL::MP_Float ET;
typedef arma::Mat<ET> mat;
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
enum KernelType {Linear, Polynomial, RBF};

class SVMachine: public IMachine {
public:
	SVMachine();
	SVMachine(KernelType t);

	virtual ~SVMachine();

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
	//ATRIBUTOS

	//Atributos pasados por parámetro
	int C_executionMode;
	std::string C_trainingFile;
	std::string C_testingFile;
	std::string C_inputFile;

	//Atributos cargados desde archivo
	VSample C_trainingSet;
	VSample C_testingSet;
	Sample C_input;

	//Usados en el training
	int C_nFeatures;
	int C_m; // Un Suppor Vector
	arma::mat C_y;
	arma::mat C_X;
	arma::mat C_SupportVectors;
	ET C_b;
	IKernel* C_kernel;

	//Usados en el testing
	//???

	//FUNCIONES

	// Internal functions
	void quadraticSolution();
	void trainByQuadraticProgramming();
};

#endif /* SVMACHINE_H_ */
