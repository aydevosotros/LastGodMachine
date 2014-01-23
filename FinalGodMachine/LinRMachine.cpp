#include "LinRMachine.h"
#include "Utils.h"

//Hay cosas hardcodeadas y tal, igual que en la LR
LinRMachine::LinRMachine() {
	//iterTrain y alphaTrain son parámetros que se hardcodean aqui
	C_iterations = 1000;
	C_alpha = 0.01;
	C_trainingType = 2; //1 normal, 2 gradiente
}

LinRMachine::~LinRMachine() {}

//Falta lo que vaya detrás del lambda
void LinRMachine::setParameters(char *argv[]) {
	std::cout << "I'm setting parameters with the LinRMachine" << std::endl;

	C_executionMode = atoi(argv[2]);
	std::cout << "Execution mode set to " << C_executionMode << std::endl;

	if(C_executionMode == 0){
		C_trainingFile = argv[3];
		C_testingFile = argv[4];

		std::cout	<< "Training with " << C_trainingFile
					<< " and testing with " << C_testingFile << std::endl;

		C_trainingType = atoi(argv[5]);

		std::cout	<< "Training type " << C_trainingType << std::endl;

		if(C_trainingType == 2){
			C_alpha = atoi(argv[6]);

			std::cout	<< "Alpha " << C_trainingType << std::endl;
		}
	} else 	if(C_executionMode == 1){
		C_inputFile = argv[3];

//		std::cout	<< "Predicting " << C_inputFile << std::endl;
	}
}

//Los loads llevan todos un apaño enlas Ys

void LinRMachine::loadTrainingSet(std::string filename) {
	std::cout << "I'm loading training set with the LinRMachine from " << filename << std::endl;

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

void LinRMachine::loadTestingSet(std::string filename) {
	std::cout << "I'm loading testing set with the LinRMachine from " << filename << std::endl;

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

//Cargo el input, y el result lo pongo a 0
void LinRMachine::loadInput(std::string filename) {
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

void LinRMachine::loadThetas(std::string filename) {
//	std::cout << "I'm loading Thetas with the LinRMachine from " << filename << std::endl;

	std::string line;
	std::ifstream thetasFile(filename.c_str());

	if(thetasFile.is_open()){
		while(std::getline(thetasFile,line)) {
			C_theta.push_back(atof(line.c_str()));
		}

		thetasFile.close();
	} else{
		std::cout << "Unable to open file" << std::endl;
	}
}

void LinRMachine::run(){
	std::cout << "I'm running the mode ";

	if(C_executionMode == 0){
		std::cout << "Test" << std::endl;

		loadTrainingSet(C_trainingFile);
		loadTestingSet(C_testingFile);

//		//Comprobamos que se han cargado bien los dos archivos
//
//		for(unsigned int i = 0; i < C_trainingSet.size(); i++){
//			for(unsigned int j = 0; j < C_trainingSet[i].getInput().size(); j++){
//				std::cout << C_trainingSet[i].getInput()[j] << ' ';
//			}
//			std::cout << std::endl << C_trainingSet[i].getRResult() << std::endl;
//		}
//
//		std::cout << std::endl;
//
//		for(unsigned int i = 0; i < C_testingSet.size(); i++){
//			for(unsigned int j = 0; j < C_testingSet[i].getInput().size(); j++){
//				std::cout << C_testingSet[i].getInput()[j] << ' ';
//			}
//			std::cout << std::endl << C_testingSet[i].getRResult() << std::endl;
//		}
//
//		//Fin de la comprobacion

		train();
		test();
	} else if(C_executionMode == 1){
//		std::cout << "Predict" << std::endl;

		loadThetas("LR_C_theta.txt");
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
//		std::cout << std::endl << C_input.getRResult() << std::endl;
//
//		//Fin de la comprobacion

		predict(C_input);

		//Escribir lo que devuelve input en algun lado?
	}
}

//Lleva dentro el isTrainingReady
void LinRMachine::train(){
	std::cout << "I'm training with the LinRMachine" << std::endl;

	C_nFeatures=C_trainingSet[0].getNFeatures();

	if(C_trainingType == 2){
//		trainByGradient(iterTrain, alphaTrain);
	} else{
		trainByNormal();
	}

	//Ahora averiguaremos el nombre que debe tener el archivo de thetas

	std::string command = "mkdir -p ";

	std::vector<std::string> trainingFileParts(Utils::split(C_trainingFile,'-'));

	std::string root = trainingFileParts[0].substr(0,10);

	std::string machinefolder = "LinR/";

	std::string value = trainingFileParts[0].substr(10,trainingFileParts[0].length());

	std::string route = "";

	route.append(root);

	route.append(machinefolder);

	route.append(value);	route.append("/");

	command.append(route);

	system(command.c_str());

//	std::cout << "El comando ha sido: "<< std::endl << command << std::endl;

	std::string prefix = "";

	prefix.append(root);
	prefix.append(value);

	std::string thetaName = C_trainingFile.substr(prefix.length()+1,C_trainingFile.length());

	route.append(thetaName);

	C_thetaFileName = route;

//	std::cout << "EL archivo creado es: " << C_thetaFileName << std::endl;

	//Y para terminar, escribimos las thetas en un archivo

	std::string line;
	std::ofstream thetasFile(C_thetaFileName.c_str());

	if(thetasFile.is_open()){
		thetasFile << C_theta[0];

		for(unsigned int i = 1; i < C_theta.size(); i++){
			thetasFile << "\n" << C_theta[i];
		}

		thetasFile.close();
	} else{
		std::cout << "Unable to open file" << std::endl;
	}
}

//Ys provisionales
void LinRMachine::test(){
	double treshold = 0.0;

//	std::cout << "I'm testing with the LinRMachine" << std::endl;

	fillActualY();

	std::vector<double> auxY;

	for(unsigned int i = 0; i < C_testingSet.size(); i++){
		double p = (double)predict(C_testingSet[i]);

		std::cout << p << std::endl;

		if((p>treshold && C_actualY[i] > 0) || (p<=treshold && C_actualY[i] < 0)){
			if(p>treshold){
				std::cout << "Predigo que el siguiente periodo será de subida" << std::endl;
			} else {
				std::cout << "Predigo que el siguiente periodo será de bajada" << std::endl;
			}

			std::cout << "Ni Sandro Rey" << std::endl;

		} else if((p>treshold && C_actualY[i] < 0) || (p<=treshold && C_actualY[i] > 0)){
			if(p>treshold){
				std::cout << "Predigo que el siguiente periodo será de subida" << std::endl;
			} else {
				std::cout << "Predigo que el siguiente periodo será de bajada" << std::endl;
			}

			std::cout << "Pinyico..." << std::endl;
		} else {
			std::cout << "No se que carajo ha pasado" << std::endl;
		}

		C_predictedY.push_back(p);
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

//Este es el moreno, no hay que tocar?
double LinRMachine::predict(Sample input){
//	std::cout << "I'm predicting this input with the LinRMachine" << std::endl;

	// Como tengo un sigmoide, con un threshold voy to cheto
	double p = 0.0;

	for(int i=0; i<C_nFeatures+1; i++){
		if(i==0) {
			p = C_theta[i];
		} else {
			p += C_theta[i]*input.getInput()[i-1];
		}
	}

	return p;
}

//Correcto
void LinRMachine::clearTrainingSet() {
	C_trainingSet.clear();
}

//double LinRMachine::sigmoid(double z) {
//	double e = 2.71828182845904523536;
//	return 1/(1+pow(e,-z));
//}

////Presuntamente correcto, y las Ys?
//double LinRMachine::cost(std::vector<double> theta, std::vector<std::vector<double> > X, std::vector<double> y) {
//	double J = 0.0;
//	for(unsigned int i=0; i<y.size(); i++){
//		// Calculo el valor de la hipótises para la theta dada
//		double h = 0.0;
//		for(unsigned int j=0; j<theta.size(); j++){
//			h += theta[j]*X[i][j];
//		}
//		h = sigmoid(h);
//		// Calculo el valor del coste para la theta dada
//		J+=(-y[i]*std::log(h))-((1-y[i])*std::log(1-h));
//	}
//	return J/y.size();
//}

////Presuntamente correcto, y las Ys? No se le llama O.O
//void LinRMachine::grad(std::vector<double> tetha, std::vector<std::vector<double> > X, std::vector<double> y, std::vector<double> grad) {
//	for(unsigned int j=0; j<C_theta.size(); j++){
//		double parcial = 0.0;
//		for(unsigned int i=0; i<y.size(); i++){
//			// Calculo el valor de la hipótises para la theta dada
//			double h = 0.0;
//			for(unsigned int k=0; k<C_theta.size(); k++){
//				h += C_theta[k]*X[i][k];
//			}
//			h = sigmoid(h);
//			parcial += (h-y[i])*X[i][j];
//		}
//		grad[j] = parcial/C_theta.size();
//	}
//}

////Todito comentadito estaba
//void LinRMachine::trainByGradientAdvanced(int iter, double alpha) {
////	int i, ret = 0;
////	lbfgsfloatval_t fx;
////	lbfgsfloatval_t *theta = lbfgs_malloc(X.size());
////	lbfgs_parameter_t param;
////
////	if (theta == NULL) {
////		printf("ERROR: Failed to allocate a memory block for variables.\n");
////	}
////
////	/* Initialize the variables. */
////	for (i = 0;i < X.size();i += 2) {
////		theta[i] = this->theta[i];
////	}
////
////	/* Initialize the parameters for the L-BFGS optimization. */
////	lbfgs_parameter_init(&param);
////	/*param.linesearch = LBFGS_LINESEARCH_BACKTRACKING;*/
////
////	/*
////		Start the L-BFGS optimization; this will invoke the callback functions
////		evaluate() and progress() when necessary.
////	 */
////	ret = lbfgs(X.size(), theta, NULL, evaluateLR, progressLR, NULL, &param);
////
////	/* Report the result. */
////	printf("L-BFGS optimization terminated with status code = %d\n", ret);
////	printf("  fx = %f, x[0] = %f, x[1] = %f\n", fx, theta[0], theta[1]);
////
////	lbfgs_free(theta);
//}

////Ys provisionales, y más cosas
//void LinRMachine::trainByGradient(int iter, double alpha) {
//	double vari = 0.01;
//	double pCoste = 0.0;
//	std::vector<double> gradiente;
//	fillX();
//	fillTheta();
//	fillY();
//
//	for(int k=0; k<iter; k++){
//		// Calculo el coste
//		double coste = cost(C_theta, C_X, C_y[0]);
//		std::cout << "Para la iteración " << k << " el coste es: " << coste << std::endl;
//		// Recalculo theta para la siguiente iteracion
//		grad(C_theta, C_X, C_y[0], gradiente);
////		std::cout << "El nuevo theta para la it " << k << " es: ";
//		for(unsigned int i=0; i<C_theta.size(); i++){
//			C_theta[i]=C_theta[i]-alpha*gradiente[i];
////			std::cout << theta[i]-alpha*gradiente[i] << " (" << alpha*gradiente[i] << ") ";
//		}
////		std::cout << std::endl;
//		vari = std::abs(coste-pCoste);
//		std::cout << "La variación en el coste para la iteración "<< k <<" es de: " << vari << std::endl;
//		if(vari < 0.0001 && !std::isnan(vari)){ // Truquillo porque a veces es nan
//			std::cout << "Estoy suficientemente entrenado!!!!!!\n";
//			break;
//		} else if (std::isnan(vari)){
//			std::cout << "Tengo un NaN!!!!\n";
//		}
//		pCoste = coste;
//	}
//}

//Ys provisionales
void LinRMachine::trainByNormal() {
	C_nFeatures = C_trainingSet[0].getInput().size();

	std::cout << "nFeatures es " << C_nFeatures << std::endl;

	// Obtengo la X
	arma::mat X = arma::mat(C_trainingSet.size(), C_nFeatures+1);

	for(unsigned int i = 0; i < C_trainingSet.size(); i++){
		for(int j = 0; j < C_nFeatures+1; j++){
			if(j==0){
				X(i,j) = 1.0;
			} else{
				X(i,j) = C_trainingSet[i].getInput()[j-1];
			}
		}
	}

	std::cout << "X es " << X << std::endl;

	// Obtengo la Y
	arma::mat y = arma::mat(C_trainingSet.size(), 1);

	for(unsigned int i=0; i<C_trainingSet.size(); i++){
		y(i) = (double)C_trainingSet[i].getRResult();
	}

	std::cout << "y es " << y << std::endl;

	// Inicializo theta
	arma::mat theta = arma::mat(C_nFeatures+1, 1);

	// Calculo vectorialmente
	theta = arma::pinv(X.t()*X)*X.t()*y;

//	std::cout << theta;
	C_theta.clear();

	for(int i = 0; i < C_nFeatures+1; i++){
		C_theta.push_back(theta(i));
	}
}

void LinRMachine::fillX() {
	for(unsigned int i=0; i<C_trainingSet.size(); i++){
		for(int j=0; j<C_nFeatures+1; j++){
			if(j==0)
				C_X[i][j] = 1.0;
			else C_X[i][j] = C_trainingSet[i].getInput()[j-1];
		}
	}
}

void LinRMachine::fillTheta() {
	for(int i=0; i<C_nFeatures+1; i++) {
		C_theta.push_back(0.5);
	}
}
//Ys adaptadas
void LinRMachine::fillY() {
	std::vector<double> aux;

	for(unsigned int i=0; i<C_trainingSet.size(); i++){
		C_y.push_back((double)C_trainingSet[i].getRResult());
	}
}
//Ys adaptadas
void LinRMachine::fillActualY(){
	std::vector<double> aux;

	for(unsigned int i=0; i<C_trainingSet.size(); i++){
		C_actualY.push_back((double)C_trainingSet[i].getRResult());
	}
}
