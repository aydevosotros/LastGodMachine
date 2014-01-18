#include "SVMachine.h"

SVMachine::SVMachine() {
	C_kernel = new LinearKernel();
	C_nFeatures = 0;
	C_m = 0;
}

SVMachine::SVMachine(KernelType t) {
	C_nFeatures = 0;
	C_m = 0;

	switch(t){
	case Linear:
		C_kernel = new LinearKernel();
		break;
	case Polynomial:
		C_kernel = new PolynomialKernel(2);
		break;
	case RBF:
		C_kernel = new RBFKernel();
		break;
	default:
		C_kernel = new LinearKernel();
	}
}

SVMachine::~SVMachine() {}

void SVMachine::setParameters(char *argv[]){
//	std::cout << "I'm setting parameters with the SVMachine" << std::endl;

	//esta variable luego se sustituirá por la variable de clase

	C_executionMode = atoi(argv[2]);
//	std::cout << "Execution mode set to " << C_executionMode << std::endl;

	if(C_executionMode == 0){
		C_trainingFile = argv[3];
		C_testingFile = argv[4];

//		std::cout	<< "Training with " << C_trainingFile
//					<< " and testing with " << C_testingFile << std::endl;
	} else 	if(C_executionMode == 1){
		C_inputFile = argv[3];

//		std::cout	<< "Predicting " << C_inputFile << std::endl;
	}

	int margin = atoi(argv[4]);

	if(margin == 0){
//		std::cout << "The margin is soft" << std::endl;
	} else if(margin == 1){
//		std::cout << "The margin is hard" << std::endl;
	}
}

//copypasteao tal cual de la LR
void SVMachine::loadTrainingSet(std::string filename){
//	std::cout << "I'm loading training set with the SVMachine" << std::endl;

	std::string line;
	std::ifstream trainingFile(filename.c_str());

	if(trainingFile.is_open()){
		while(std::getline(trainingFile,line)) {
			Sample tmp;

			tmp.setInput(Utils::vStovD(Utils::split(line,';')));

			std::getline(trainingFile,line);

			tmp.setResult(atoi(line.c_str()));

			C_trainingSet.push_back(tmp);
		}

		trainingFile.close();
	} else{
		std::cout << "Unable to open file" << std::endl;
	}
}

//copypasteao tal cual de la LR
void SVMachine::loadTestingSet(std::string filename){
//	std::cout << "I'm loading testing set with the SVMachine" << std::endl;

	std::string line;
	std::ifstream testingFile(filename.c_str());

	if(testingFile.is_open()){
		while(std::getline(testingFile,line)) {
			Sample tmp;

			tmp.setInput(Utils::vStovD(Utils::split(line,';')));

			std::getline(testingFile,line);

			tmp.setResult(atoi(line.c_str()));

			C_testingSet.push_back(tmp);
		}

		testingFile.close();
	} else{
		std::cout << "Unable to open file" << std::endl;
	}
}

//copypasteao tal cual de la LR
void SVMachine::loadInput(std::string filename){
//	std::cout << "I'm loading input with the SVMachine" << std::endl;

	std::string line;
	std::ifstream inputFile(filename.c_str());

	if(inputFile.is_open()){
		std::getline(inputFile,line);

		C_input.setInput(Utils::vStovD(Utils::split(line,';')));

		C_input.setResult(0);

		inputFile.close();
	} else{
		std::cout << "Unable to open file" << std::endl;
	}
}

//copypaste de LR
void SVMachine::run(){
	std::cout << "I'm running the mode ";

	if(C_executionMode == 0){
		std::cout << "Test" << std::endl;

		loadTrainingSet(C_trainingFile);
		loadTestingSet(C_testingFile);

		//Comprobamos que se han cargado bien los dos archivos

		for(unsigned int i = 0; i < C_trainingSet.size(); i++){
			for(unsigned int j = 0; j < C_trainingSet[i].getInput().size(); j++){
				std::cout << C_trainingSet[i].getInput()[j] << ' ';
			}
			std::cout << std::endl << C_trainingSet[i].getResult() << std::endl;
		}

		std::cout << std::endl;

		for(unsigned int i = 0; i < C_testingSet.size(); i++){
			for(unsigned int j = 0; j < C_testingSet[i].getInput().size(); j++){
				std::cout << C_testingSet[i].getInput()[j] << ' ';
			}
			std::cout << std::endl << C_testingSet[i].getResult() << std::endl;
		}

		//Fin de la comprobacion

		train();
		test();
	} else if(C_executionMode == 1){
//		std::cout << "Predict" << std::endl;

		loadInput(C_inputFile);

//		//Comprobamos que se leen bien los archivos
//
//		for(unsigned int i = 0; i < C_theta.size(); i++){
//			std::cout << C_theta[i] << ' ';
//		}
//		std::cout << std::endl << std::endl;
//
//		for(unsigned int i = 0; i < C_input.getInput().size(); i++){
//			std::cout << C_input.getInput()[i] << ' ';
//		}
//		std::cout << std::endl << C_input.getResult() << std::endl;
//
//		//Fin de la comprobacion

		predict(C_input);

		//Escribir lo que devuelve input en algun lado?
	}
}

//lleva dentro el istrainingReady
void SVMachine::train(){
//	std::cout << "I'm training with the SVMachine" << std::endl;

	C_nFeatures=C_trainingSet[0].getNFeatures();

	trainByQuadraticProgramming();
}

void SVMachine::test(){
//	std::cout << "I'm testing with the SVMachine" << std::endl;

	fillActualY();

	for(unsigned int i = 0; i < C_testingSet.size(); i++){
		double p = predict(C_testingSet[i]);

		if((p>0.5 && C_actualY[i] > 0) || (p<=0.5 && C_actualY[i] < 0)){
			if(p>0.5){
//				std::cout << "Predigo que el siguiente periodo será de subida" << std::endl;
			} else {
//				std::cout << "Predigo que el siguiente periodo será de bajada" << std::endl;
			}

//			std::cout << "Ni Sandro Rey" << std::endl;

		} else if((p>0.5 && C_actualY[i] < 0) || (p<=0.5 && C_actualY[i] > 0)){
			if(p>0.5){
//				std::cout << "Predigo que el siguiente periodo será de subida" << std::endl;
			} else {
//				std::cout << "Predigo que el siguiente periodo será de bajada" << std::endl;
			}

//			std::cout << "Pinyico..." << std::endl;
		} else {
			std::cout << "No se que carajo ha pasado" << std::endl;
		}

		C_predictedY.push_back(p);
	}

	std::cout << "PredictedY es:" << std::endl;

	for(unsigned int i = 0; i < C_predictedY.size(); i++){
		std::cout << C_predictedY[i] << std::endl;
	}

	std::cout << "ActualY es:" << std::endl;

	for(unsigned int i = 0; i < C_actualY.size(); i++){
		std::cout << C_actualY[i] << std::endl;
	}

	//Al final, cuando tengamos lleno el C_predictedY, calculamos Precission y Recall

	double tPositives = 0.0;
	double fPositives = 0.0;
	double tNegatives = 0.0;
	double fNegatives = 0.0;

	for(unsigned int i = 0; i < C_actualY.size(); i++){
		if(C_actualY[i] > 0 && C_predictedY[i] > 0){
			tPositives++;
		} else if(C_actualY[i] > 0 && C_predictedY[i] < 0){
			fNegatives++;
		} else if(C_actualY[i] < 0 && C_predictedY[i] > 0){
			fPositives++;
		} else if(C_actualY[i] < 0 && C_predictedY[i] < 0){
			tNegatives++;
		}
	}

	double precission = tPositives / (tPositives + fPositives);

	std::cout << "Precission = " << precission << std::endl;

	double recall = tPositives / (tPositives + fNegatives);

	std::cout << "Recall = " << recall << std::endl;

	double fScore = 2 * ( (precission * recall) / (precission + recall) );

	std::cout << "fScore = " << fScore << std::endl;
}

double SVMachine::predict(Sample input){
//	std::cout << "I'm predicting with the SVMachine" << std::endl;

    ET aux(0.0);
    // Hago esto provisional para escalar
    std::vector<double> entradaScalada;
    std::vector<Sample> sInput;

    sInput.push_back(input);
//    Utils::scalation(sInput);

    arma::Col<double> Input(input.getNFeatures());

    for(int i=0; i<input.getNFeatures(); i++)
        Input(i)=sInput[0].getInput()[i];

    for(int i=0; i<C_trainingSet.size(); i++){
        if(C_SupportVectors.at(i) > 0.0){
        	std::cout << "X:" << std::endl;
        	std::cout << C_X.row(i).t() << std::endl;
        	std::cout << "input:" << std::endl;
        	std::cout << Input << std::endl;

            aux += ET(C_SupportVectors.at(i))*ET(C_y.at(i))*C_kernel->K(C_X.row(i).t(), Input);
//            std::cout << "La suma auxiliar vale: " << aux+b << std::endl;
        }
    }

    std::cout << std::endl << "He ejecutado hasta aqui" << std::endl;

    double p = CGAL::to_double(aux + C_b);

    if(p > 1){
    	return 1.0;
    } else if(p < -1){
    	return -1.0;
    }
}

void SVMachine::clearTrainingSet(){
	C_trainingSet.clear();
}

//bool SVMachine::isTrainingReady() {
//	if(trainingSet.size() > 0){
//		if(trainingSet.size() == 1)
//			nFeatures=trainingSet[0].getNFeatures();
//		if(trainingSet.size() > nFeatures*7 ){
//			trainByQuadraticProgramming();
//			return true;
//		}
//	} else return false;
//}

//void SVMachine::classifySample(Sample sample) {
//	ET aux(0.0);
//	// Hago esto provisional para escalar
//	std::vector<double> entradaScalada;
//	std::vector<Sample> sInput;
//	sInput.push_back(sample);
//	Utils::scalation(sInput);
//	arma::Col<double> Input(sample.getNFeatures());
//	for(int i=0; i<sample.getNFeatures(); i++)
//		Input(i)=sInput[0].input[i];
//	for(int i=0; i<trainingSet.size(); i++){
//		if(SupportVectors.at(i) > 0.0){
//			aux += ET(SupportVectors.at(i))*ET(y.at(i))*kernel->K(X.row(i).t(), Input);
////			std::cout << "La suma auxiliar vale: " << aux+b << std::endl;
//		}
//	}
//	double p = CGAL::to_double(aux + b);
//	std::cout << "Para este sample tenemos una p de: " << p << std::endl;
//	if((p>0 && sample.burn) || (p<=-1 && !sample.burn)){
//		if(p>0)
//			std::cout << "Predigo que la siguiente puerta está encendida" << std::endl;
//		else if(p<0) std::cout << "Predigo que la siguiente puerta está apagada" << std::endl;
//		std::cout << "Ha clasificao de puta madre" << std::endl;
//		this->classifySuccesses++;
//	} else if ((p<=0 && sample.burn) || (p>0 && !sample.burn)){
//		if(p>0)
//			std::cout << "Predigo que la siguiente puerta está encendida" << std::endl;
//		else if(p<0) std::cout << "Predigo que la siguiente puerta está apagada" << std::endl;
//		std::cout << "Pinyico... volviendo a entrenar" << std::endl;
////		this->trainingSet.push_back(sample);
////		this->trainByQuadraticProgramming();
//		this->classifySuccesses--;
//	} else std::cout << "No se que carajo ha pasado" << std::endl;
//	std::cout << "He clasificado correctamente " << classifySuccesses << std::endl;
//}

//bool SVMachine::isDoorOnFire(double input[]) {
//	ET aux(0.0);
//	std::vector<double> entradaScalada;
//	for(int i=0; i<nFeatures; i++)
//		entradaScalada.push_back(input[i]);
//	std::vector<Sample> sInput;
//	Sample s;
//	s.input = entradaScalada;
//	sInput.push_back(s);
//	Utils::scalation(sInput);
//	arma::Col<double> Input(nFeatures);
//	for(int i=0; i<nFeatures; i++)
//		Input(i)=sInput[0].input[i];
//	for(int i=0; i<trainingSet.size(); i++){
//		if(SupportVectors.at(i) > 0.0){
//			aux += ET(SupportVectors.at(i))*ET(y.at(i))*kernel->K(X.row(i).t(), Input);
//			std::cout << "La suma auxiliar vale: " << aux+b << std::endl;
//		}
//	}
//	double p = CGAL::to_double(aux + b);
//	std::cout << "La probabilidad de que la siguiente puerta esté caliente es: " << p << std::endl;
//	if(p>1)
//		return true;
//	else if(p<-1) return false;
//
//	return true;
//}

//Está un poco fuzzy, habrá que estructurarlo y tal, pero correcto
void SVMachine::quadraticSolution() {
	int n = C_trainingSet.size();
	int m = 1; // Entiendo que es el numero de restricciones
	Program qp (CGAL::EQUAL);

	// Obtengo la X
//	Utils::scalation(C_trainingSet); // Escalado de parámetros

	std::cout << "n vale: " << n << std::endl;
	std::cout << "nFeatures vale: " << C_nFeatures << std::endl;
	C_X = arma::mat(n, C_nFeatures);

	for(int i = 0; i < n; i++){
		for(int j = 0; j < C_nFeatures; j++){
			C_X(i,j) = C_trainingSet[i].getInput()[j];
		}
	}
//	std::cout << C_X;

	// Obtengo la Y
	C_y = arma::mat(n, 1);

	std::cout << "n vale: " << n << std::endl;
	for(int i = 0; i < n; i++){
		C_y(i) = C_trainingSet[i].getResult();
	}

	std::cout << C_y;
	// Seteo la restriccion
	for(int i = 0; i < n; i++){
		qp.set_a(i,0,ET(C_y.at(i)));
		qp.set_l(i,true,ET(0));
		qp.set_u(i,false);
		qp.set_c(i,ET(-1));
//		std::cout << "y(" << i << "): " << y.at(i) << std::endl;
	}

	qp.set_b(0,ET(0));
	qp.set_r(0,CGAL::EQUAL);
	qp.set_c0(ET(0));

	// Seteo la symmetric positive-semidefinite matrix
	for(int i = 0; i < n; i++){
		for(int j = 0; j<=i; j++){
			ET ip = C_kernel->K(C_X.row(i).t(),C_X.row(j).t());
			std::cout << "El kernel para " << i << "," << j << " nos dice que el innerproduct es: " << ip << std::endl;
			ET daux = ip*ET(C_y.at(i))*ET(C_y.at(j));
			std::cout << "El producto de " << i << "," << j << ": " << daux << std::endl;
			qp.set_d(i,j,daux);
			std::cout << "La matriz auxiliar vale:" <<  daux << std::endl;
		}
	}

	 // solve the program, using ET as the exact type
	Solution s = CGAL::solve_quadratic_program(qp, ET());
	// print basic constraint indices (we know that there is only one: 1)
	std::cout << "Y la solución es: " << s << std::endl;
//	arma::mat W = arma::mat(n,1);

	C_SupportVectors = arma::mat(n,1);

	ET sumaB(0.0);

	if(s.is_optimal()) { // we know that, don't we?
		int i = 0;
		for (Solution::Variable_value_iterator it = s.variable_values_begin(); it != s.variable_values_end(); ++it){
			C_SupportVectors(i) = CGAL::to_double(*it);
			if(C_SupportVectors.at(i) != 0.0){
				C_m = i; // Esto lo hago para obtener un sv que me resuelva la b
			}
			i++;
		}
		// Calculo la b
		for(int i=0; i<n; i++)
			if(C_SupportVectors.at(i) != 0.0)
				sumaB += ET(C_SupportVectors.at(i))*ET(C_y.at(i))*C_kernel->K(C_X.row(i).t(), C_X.row(C_m).t());
		C_b = ET(C_y(C_m)) - sumaB;
		std::cout << "Y el valor de b es: "<< C_b << std::endl;
	} else std::cout << "No es optima, vete tu a saber por qué...\n";

//	int pausa; std::cin >> pausa;
}

void SVMachine::trainByQuadraticProgramming() {
	quadraticSolution(); // Esto me da los Support Vectors
}

void SVMachine::fillActualY(){
	for(unsigned int i=0; i<C_testingSet.size(); i++){
		C_actualY.push_back((double)C_testingSet[i].getResult());
	}
}
