/*
 * NNMachine.cpp
 *
 *  Created on: Jan 16, 2014
 *      Author: antonio
 */

#include "NNMachine.h"

NNMachine::NNMachine() {

	s_l.push_back(2);
	s_l.push_back(2);
	s_l.push_back(1);
	L = s_l.size();
	train();
}

NNMachine::~NNMachine() {
	// TODO Auto-generated destructor stub
}

void NNMachine::setParameters(char* argv[]) {
}

void NNMachine::loadTrainingSet(std::string filename) {
	//	std::cout << "I'm loading training set with the LinRMachine from " << filename << std::endl;

	std::string line;
	std::ifstream trainingFile(filename.c_str());

	if(trainingFile.is_open()){
		while(std::getline(trainingFile,line)) {
			Sample tmp;

			tmp.setInput(Utils::vStovD(Utils::split(line,';')));

			std::getline(trainingFile,line);

			double res = atof(line.c_str());

			tmp.setRResult(res);

			C_trainingSet.push_back(tmp);
		}

		trainingFile.close();
	} else{
		std::cout << "Unable to open file" << std::endl;
	}
}

void NNMachine::loadTestingSet(std::string filename) {
	//	std::cout << "I'm loading testing set with the LinRMachine from " << filename << std::endl;

	std::string line;
	std::ifstream testingFile(filename.c_str());

	if(testingFile.is_open()){
		while(std::getline(testingFile,line)) {
			Sample tmp;

			tmp.setInput(Utils::vStovD(Utils::split(line,';')));

			std::getline(testingFile,line);

			double res = atof(line.c_str());

			tmp.setRResult(res);

			C_testingSet.push_back(tmp);
		}

		testingFile.close();
	} else{
		std::cout << "Unable to open file" << std::endl;
	}
}

void NNMachine::loadInput(std::string filename) {
//	std::cout << "I'm loading input with the LinRMachine from " << filename << std::endl;

	std::string line;
	std::ifstream inputFile(filename.c_str());

	if(inputFile.is_open()){
		std::getline(inputFile,line);

		C_input.setInput(Utils::vStovD(Utils::split(line,';')));

		C_input.setRResult(atof(line.c_str()));

		inputFile.close();
	} else{
		std::cout << "Unable to open file" << std::endl;
	}
}

void NNMachine::clearTrainingSet(){
	this->trainingSet.clear();
}

void NNMachine::train(){
	initTraining();
	for(int i=0; i<this->trainingSet.size(); i++){
		Sample s = this->trainingSet[i];
		forwardPropagate(s);
		backPropagate(s);
		gradChecking();
		trainByGradient(1000, 0.01);
	}
}

void NNMachine::run() {
}

void NNMachine::test() {
}

double NNMachine::predict(Sample input) {

}

void NNMachine::forwardPropagate(Sample s) {
	// Implementación vectorizada
	//Seteo el input en la primera capa
	for(int i=0; i<s_l[0]+1; i++){
		if(i==0)
			this->a[0](i) = 1.0; // Seteo el bias
		else this->a[0](i) = s.getInput()[i-1];
	}

	// Forwarding
	for(int l=1; l<L; l++){
//		std::cout << "Propago por la capa: " << l << std::endl;
		// Calculo z para la capa
		arma::mat zL = this->thetas[l-1]*this->a[l-1];
//		std::cout << "El valor de z es: " << std::endl << zL << std::endl;
		// Y calculo la activación para la capa
		if(l<L-1){
			for(int i=0; i<s_l[l]+1; i++){
				if(i==0)
					this->a[l](i)=1.0;
				else this->a[l](i)=sigmoid(zL(i-1));
			}
		} else {
			for(int i=0; i<s_l[l]; i++)
				this->a[l](i)=sigmoid(zL(i));
		}
//		std::cout << "El valor de la activación es: " << std::endl << a[l] << std::endl;
	}
}

void NNMachine::backPropagate(Sample s) {
	std::vector<arma::Col<double> > lowerDelta;
	// Inicializo los lowerDelta porque como empiezo al revés al hacer pushback y los índices y los petes...
	for(int l=0; l<L; l++){
		if(l==L-1)
			lowerDelta.push_back(arma::Col<double>(s_l[l]));
		else lowerDelta.push_back(arma::Col<double>(s_l[l]+1));
	}
	for(int l=L-1; l>0; l--){

		if(l==L-1){
			lowerDelta[l](0) = a[l](0)-s.getResult()[0]; // esto es lo que tengo que generalizar para muchas salidas
		} else {
			arma::Col<double> lowerDeltaL(s_l[l]+1);
			arma::mat gP = this->a[l]%(1-a[l]);
			arma::Col<double> aux = thetas[l].t()*lowerDelta[l+1];
			lowerDelta[l] = aux%gP;
		}

		std::cout << "Para la capa " << l << " he obtenido un lowerDelta de: " << std::endl << lowerDelta[l] << std::endl;

	}
	for(int l=0; l<L-1; l++){
		std::cout << "Calculo upperDelta para la capa: " << l << std::endl;
		if(l+1!=L-1){
			this->upperDelta[l] = this->upperDelta[l] + (lowerDelta[l+1].rows(1,s_l[l])*this->a[l].t());
		} else {
			this->upperDelta[l] = this->upperDelta[l] + (lowerDelta[l+1]*this->a[l].t());
		}
		std::cout << "El valor de upperDelta es: " << std::endl << upperDelta[l] << "para un theta: " << std::endl << thetas[l] << std::endl;
	}
	// Regularizo y obtengo la D
	for(int l=0; l<L-1; l++){
		for(int i=0; i<s_l[l+1]; i++){
			for(int j=0; j<s_l[l]+1; j++){
				if(j==0)
					this->D[l](i,j) = (1.0/this->trainingSet.size())*this->upperDelta[l](i,j);
				else
					this->D[l](i,j) = (1.0/this->trainingSet.size())*this->upperDelta[l](i,j)+(lambda*this->thetas[l](i,j));
				std::cout << "El valor de D para (" << l << "," << i << "," << j << ",) es : " << D[l](i,j) << std::endl;
			}
		}
	}
}

void NNMachine::initTraining() {
	// Init thetas and a
	this->thetas.clear();
	for(int l=0; l<L; l++){
		if(l>0){
			arma::mat thetaL(s_l[l+1], s_l[l]+1);
			// Random init
			for(int i=0; i<s_l[l+1]; i++)
				for(int j=0; j<s_l[l]+1; j++)
					thetaL(i,j) = Utils::uniformRandomDouble(-999.0,999.0);
			this->thetas.push_back(thetaL);
			this->upperDelta.push_back(arma::mat(s_l[l+1], s_l[l]+1));
			this->D.push_back(arma::mat(s_l[l+1], s_l[l]+1));
		}
		if(l==L-1)
			this->a.push_back(arma::Col<double>(s_l[l]));
		else this->a.push_back(arma::Col<double>(s_l[l]+1));
	}
}

void NNMachine::initRandomThetas() {
	this->thetas.clear();
	for(int l=1; l<L; l++){
		arma::mat thetaL(s_l[l+1], s_l[l]+1);
		for(int i=0; i<s_l[l+1]; i++)
			for(int j=0; j<s_l[l]+1; j++)
				thetaL(i,j) = Utils::uniformRandomDouble(-999.0,999.0);
		this->thetas.push_back(thetaL);
	}
}

void NNMachine::initTrainingXNOR() {
	// Init thetas and a
	this->thetas.clear();
	arma::mat thetaL1(2,3);
	thetaL1(0,0)=-30.0;
	thetaL1(0,1)=20.0;
	thetaL1(0,2)=20.0;
	thetaL1(1,0)=10.0;
	thetaL1(1,1)=-20.0;
	thetaL1(1,2)=-10.0;
	this->thetas.push_back(thetaL1);
	arma::mat thetaL2(1,3);
	thetaL2(0,0) = -10.0;
	thetaL2(0,1) = 20.0;
	thetaL2(0,2) = 20.0;
	this->thetas.push_back(thetaL2);
	// Inicializo los a
	for(int l=0; l<L; l++){
		if(l==L-1)
			this->a.push_back(arma::Col<double>(s_l[l]));
		else{
			this->a.push_back(arma::Col<double>(s_l[l]+1));
			this->D.push_back(arma::mat(s_l[l+1], s_l[l]+1));
		}
		this->upperDelta.push_back(arma::mat(s_l[l+1], s_l[l]+1));

	}
}

double NNMachine::sigmoid(double z) {
	double e = 2.71828182845904523536;
	return 1/(1+pow(e,-z));
}

void NNMachine::gradChecking() {
//	// Unas cosas previas pa tener que probar
//	Sample s;
//	std::vector<double> input;
//	input.push_back(0);
//	input.push_back(1);
//	s.setInput(input);
//	std::vector<int> result;
//	result.push_back(1);
//	s.setResult(result);
//	this->trainingSet.push_back(s);
//
//	// Con esto hago una thetas y fp and bp
//	this->initTrainingXNOR();
//	this->forwardPropagate(s);
//	this->backPropagate(s);

	std::vector<arma::mat> cThetasPlus;
	std::vector<arma::mat> cThetasMinus;

	double epsilon = 0.001; // Esto tiene que entrar por parámetro
	// Inicializo los thetas random
//	initRandomThetas();
	// Calculo el coste sumando y restando epsilon a nuestro theta
	std::cout << "Voy por aquí " << std::endl;
	for(int l=0; l<L-1; l++){
		arma::mat cTPL(s_l[l+1], s_l[l]+1);
		arma::mat cTML(s_l[l+1], s_l[l]+1);
		for(int i=0; i<s_l[l+1]; i++){
			for(int j=0; j<s_l[l]+1; j++){
				std::cout << "Voy por aquí " << l << "," << i << "," << j << std::endl;
				this->thetas[l](i,j) += epsilon;
				cTPL(i,j) = cost();
				this->thetas[l](i,j) -= 2*epsilon;
				cTML(i,j) = cost();
				this->thetas[l](i,j) += epsilon;
			}
		}
		cThetasPlus.push_back(cTPL);
		cThetasMinus.push_back(cTML);
	}
	// Calculo la aproximación
	std::cout << "Voy por aquí " << std::endl;
	std::vector<arma::mat> gradAprox;
	for(int l=0; l<L-1; l++){
		gradAprox.push_back(arma::mat(s_l[l+1], s_l[l]+1));
		for(int i=0; i<s_l[l+1]; i++){
			for(int j=0; j<s_l[l]+1; j++){
				gradAprox[l](i,j) = (cThetasPlus[l](i,j)-cThetasMinus[l](i,j))/(2*epsilon);
				std::cout << "Aquí empiezo a comprobar la maraña" << std::endl;
				std::cout << "Para la capa " << l << " desde el nodo " << i << " al nodo " << j <<
						" tengo un aproximado de: " << gradAprox[l](i,j) << " y una DX " << this->D[l](i,j) << std::endl;
			}
		}
	}
}

double NNMachine::cost(){
	double J = 0.0;
	for(int i=0; i<this->trainingSet.size(); i++){
		this->forwardPropagate(trainingSet[i]);
		for(int k=0; k<s_l[L-1]; k++){
			J += trainingSet[i].getResult()[k] * std::log(a[L-1](k)) + (1-trainingSet[i].getResult()[k])*std::log(1-a[L-1](k));
		}
	}
	J /= trainingSet.size()*(-1.0);
	std::cout << "LLego hasta aquí con un coste de: " << J << std::endl;
	double aux = 0.0;
	for(int l=1; l<L; l++)
		for(int i=0; i<s_l[l+1]; i++)
			for(int j=0; j<s_l[l]+1; j++)
				aux+=std::pow(this->thetas[l](i,j),2);
	aux*=this->lambda;
	aux/=2*this->trainingSet.size();
	return J+aux;
}

void NNMachine::trainByGradient(int iter, double alpha) {
	double pCoste = 0.0;
	for(int k=0; k<iter; k++){
		// Calculo el coste
		double coste = cost();
		std::cout << "Para la iteración " << k << " el coste es: " << coste << std::endl;
		// Recalculo theta para la siguiente iteracion
//		std::cout << "El nuevo theta para la it " << k << " es: ";
		for(int l=1; l<L; l++)
			for(int i=0; i<s_l[l+1]; i++)
				for(int j=0; j<s_l[l]+1; j++)
					this->thetas[l](i,j)+=alpha*this->D[l](i)(j);
		}
		vari = std::abs(cost()-pCoste);
		std::cout << "La variación en el coste para la iteración "<< k <<" es de: " << vari << std::endl;
		if(vari < 0.0001 && !std::isnan(vari)){ // Truquillo porque a veces es nan
			std::cout << "Estoy suficientemente entrenado!!!!!!\n";
			break;
		} else if (std::isnan(vari)){
			std::cout << "Tengo un NaN!!!!\n";
		}
		pCoste = coste;
	}
}
