#include "LRMachine.h"

//En el constructor no se que poner
LRMachine::LRMachine() {
	C_nFeatures = 4;
	C_classifySuccesses = 0;
	iterTrain = 1000;
	alphaTrain = 0.01;
	trainType = 1; //1 normal, 2 gradiente
}

LRMachine::~LRMachine() {}

//Falta lo que vaya detrás del lambda
void LRMachine::setParameters(char *argv[]) {
	std::cout << "I'm setting parameters with the LRMachine" << std::endl;

	C_executionMode = atoi(argv[2]);
	std::cout << "Execution mode set to " << C_executionMode << std::endl;

	if(C_executionMode == 0){
		C_trainingFile = argv[3];
		C_testingFile = argv[4];

		std::cout	<< "Training with " << C_trainingFile
					<< " and testing with " << C_testingFile << std::endl;

		C_lambda = atoi(argv[5]);
		std::cout << "Lambda set to " << C_lambda << std::endl;
	} else 	if(C_executionMode == 1){
		C_inputFile = argv[3];

		std::cout	<< "Predicting " << C_inputFile << std::endl;

		C_lambda = atoi(argv[4]);
		std::cout << "Lambda set to " << C_lambda << std::endl;
	}

//	Algo más a partir de aquí
}

//Falta ver estructura del fichero
void LRMachine::loadTrainingSet(std::string filename) {
	std::cout << "I'm loading training set with the LRMachine from " << filename << std::endl;

	std::string line;
	std::ifstream trainingFile(filename.c_str());

	if(trainingFile.is_open()){
		while(std::getline(trainingFile,line)) {
			//Aquí se leería lo que fuera y se guardaría en la variable
			std::cout << line << std::endl;
		}

		trainingFile.close();
	} else{
		std::cout << "Unable to open file" << std::endl;
	}
}

void LRMachine::loadTestingSet(std::string filename) {
	std::cout << "I'm loading testing set with the LRMachine from " << filename << std::endl;

	std::string line;
	std::ifstream testingFile(filename.c_str());

	if(testingFile.is_open()){
		while(std::getline(testingFile,line)) {
			//Aquí se leería lo que fuera y se guardaría en la variable
			std::cout << line << std::endl;
		}

		testingFile.close();
	} else{
		std::cout << "Unable to open file" << std::endl;
	}
}

void LRMachine::loadInput(std::string filename) {
	std::cout << "I'm loading input with the LRMachine from " << filename << std::endl;

	std::string line;
	std::ifstream inputFile(filename.c_str());

	if(inputFile.is_open()){
		while(std::getline(inputFile,line)) {
			//Aquí se leería lo que fuera y se guardaría en la variable
			std::cout << line << std::endl;
		}

		inputFile.close();
	} else{
		std::cout << "Unable to open file" << std::endl;
	}
}

//Correcto?
void LRMachine::loadThetas(std::string filename) {
	std::cout << "I'm loading Thetas with the LRMachine from " << filename << std::endl;

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

//	Lee bien las thetas?
//	for(unsigned int i = 0; i < C_theta.size(); i++){
//		std::cout << C_theta[i] << std::endl;
//	}
}

//Correcto?
void LRMachine::run(){
	std::cout << "I'm running the mode ";

	if(C_executionMode == 0){
		std::cout << "Test" << std::endl;

		loadTrainingSet(C_trainingFile);
		loadTestingSet(C_testingFile);

		train();
		test();
	} else if(C_executionMode == 1){
		std::cout << "Predict" << std::endl;

		loadThetas("LR_C_theta.txt");
		loadInput(C_inputFile);

		predict();
	}
}

//Cuidadito con el nFeatures hardcodeao que hay aqui
void LRMachine::train(){
	std::cout << "I'm training with the LRMachine" << std::endl;

	C_nFeatures = 5; //Esto es temporal as hell
	fillTheta();
	fillY();

	//Toa la shit

	//Y para terminar, escribimos las thetas en un archivo

	std::string line;
	std::ofstream thetasFile("LR_C_theta.txt");

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

void LRMachine::test(){
	std::cout << "I'm testing with the LRMachine" << std::endl;

	fillActualY();

	//Al final, cuando tengamos lleno el C_obtainedY, calculamos Precission y Recall

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
	double recall = tPositives / (tPositives + fNegatives);
	double fScore = 2 * ( (precission * recall) / (precission + recall) );

	//Y escribirlos en el formato adecuado
}

//Está copypasteado el classifySample
void LRMachine::predict(){
	std::cout << "I'm predicting this input with the LRMachine" << std::endl;

//	// Como tengo un sigmoide, con un threshold voy to cheto
//	double p = 0.0;
//	for(int i=0; i<C_nFeatures+1; i++){
//		if(i==0)
//			p = C_theta[i];
//		else p += C_theta[i]*input.input[i-1];
//	}
//	p=sigmoid(p);
//	if((p>0.5 && input.burn) || (p<=0.5 && !input.burn)){
//		if(p>0.5)
//			std::cout << "Predigo que la siguiente puerta está encendida" << std::endl;
//		else std::cout << "Predigo que la siguiente puerta está apagada" << std::endl;
//		std::cout << "Ha clasificao de puta madre" << std::endl;
//		this->C_classifySuccesses++;
//	} else if ((p<=0.5 && input.burn) || (p>0.5 && !input.burn)){
//		if(p>0.5)
//			std::cout << "Predigo que la siguiente puerta está encendida" << std::endl;
//		else std::cout << "Predigo que la siguiente puerta está apagada" << std::endl;
//		std::cout << "Pinyico... volviendo a entrenar" << std::endl;
//		this->C_trainingSet.push_back(input);
//		if(trainType == 2)this->trainByGradient(iterTrain, alphaTrain);
//		else this->trainByNormalEcuation();
//		this->C_classifySuccesses--;
//	} else std::cout << "No se que carajo ha pasado" << std::endl;
//	std::cout << "He clasificado correctamente " << C_classifySuccesses << std::endl;

}

//Correcto
void LRMachine::clearTrainingSet() {
	C_trainingSet.clear();
	C_classifySuccesses = 0;
}

//bool LRMachine::isTrainingReady() {
//	if(trainingSet.size() == 1){
//		nFeatures=trainingSet[0].getNFeatures();
//	}
//	if(trainingSet.size() > 20 ){
//		if(trainType == 2)trainByGradient(iterTrain, alphaTrain);
//		else trainByNormalEcuation();
//		return true;
//	} else return false;
//}

//bool LRMachine::isReadyToCross() {
//	return classifySuccesses > 10;
//}

//void LRMachine::classifySample(Sample sample) {

//}

//bool LRMachine::isDoorOnFire(double input[]) {
//	double p = 0.0;
//	for(int i=0; i<nFeatures+1; i++){
//		if(i==0)
//			p = theta[i];
//		else p += theta[i]*input[i-1];
//	}
//	p=sigmoid(p);
//	std::cout << "La probabilidad de que la siguiente puerta esté caliente es: " << p << std::endl;
////	if(p>0.4 && p <0.6)
//	if(p>0.40)
//		return true; // Esto es un truquillo para no jugarsela en un rango de más indecisión
////	if(p>0.5)
////		return true;
//	else return false;
//}

//Correcto
double LRMachine::sigmoid(double z) {
	double e = 2.71828182845904523536;
	return 1/(1+pow(e,-z));
}

//Presuntamente correcto
double LRMachine::cost(std::vector<double> theta, std::vector<std::vector<double> > X, std::vector<double> y) {
	double J = 0.0;
	for(unsigned int i=0; i<y.size(); i++){
		// Calculo el valor de la hipótises para la theta dada
		double h = 0.0;
		for(unsigned int j=0; j<theta.size(); j++){
			h += theta[j]*X[i][j];
		}
		h = sigmoid(h);
		// Calculo el valor del coste para la theta dada
		J+=(-y[i]*std::log(h))-((1-y[i])*std::log(1-h));
	}
	return J/y.size();
}

//Presuntamente correcto
void LRMachine::grad(std::vector<double> tetha, std::vector<std::vector<double> > X, std::vector<double> y, std::vector<double> grad) {
	for(unsigned int j=0; j<C_theta.size(); j++){
		double parcial = 0.0;
		for(unsigned int i=0; i<y.size(); i++){
			// Calculo el valor de la hipótises para la theta dada
			double h = 0.0;
			for(unsigned int k=0; k<C_theta.size(); k++){
				h += C_theta[k]*X[i][k];
			}
			h = sigmoid(h);
			parcial += (h-y[i])*X[i][j];
		}
		grad[j] = parcial/C_theta.size();
	}
}

//Todito comentadito estaba
void LRMachine::trainByGradientAdvanced(int iter, double alpha) {
//	int i, ret = 0;
//	lbfgsfloatval_t fx;
//	lbfgsfloatval_t *theta = lbfgs_malloc(X.size());
//	lbfgs_parameter_t param;
//
//	if (theta == NULL) {
//		printf("ERROR: Failed to allocate a memory block for variables.\n");
//	}
//
//	/* Initialize the variables. */
//	for (i = 0;i < X.size();i += 2) {
//		theta[i] = this->theta[i];
//	}
//
//	/* Initialize the parameters for the L-BFGS optimization. */
//	lbfgs_parameter_init(&param);
//	/*param.linesearch = LBFGS_LINESEARCH_BACKTRACKING;*/
//
//	/*
//		Start the L-BFGS optimization; this will invoke the callback functions
//		evaluate() and progress() when necessary.
//	 */
//	ret = lbfgs(X.size(), theta, NULL, evaluateLR, progressLR, NULL, &param);
//
//	/* Report the result. */
//	printf("L-BFGS optimization terminated with status code = %d\n", ret);
//	printf("  fx = %f, x[0] = %f, x[1] = %f\n", fx, theta[0], theta[1]);
//
//	lbfgs_free(theta);
}

//Usa funciones dependientes de Sample
void LRMachine::trainByGradient(int iter, double alpha) {
	double vari = 0.01;
	double pCoste = 0.0;
	std::vector<double> gradiente;
	fillX();
	fillTheta();
	fillY();

	for(int k=0; k<iter; k++){
		// Calculo el coste
		double coste = cost(C_theta, C_X, C_y);
		std::cout << "Para la iteración " << k << " el coste es: " << coste << std::endl;
		// Recalculo theta para la siguiente iteracion
		grad(C_theta, C_X, C_y, gradiente);
//		std::cout << "El nuevo theta para la it " << k << " es: ";
		for(unsigned int i=0; i<C_theta.size(); i++){
			C_theta[i]=C_theta[i]-alpha*gradiente[i];
//			std::cout << theta[i]-alpha*gradiente[i] << " (" << alpha*gradiente[i] << ") ";
		}
//		std::cout << std::endl;
		vari = std::abs(coste-pCoste);
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

//Ya estaba comentado cuando llegué
void LRMachine::trainByNormalEcuation() {
//	// Actualizo aqui el número de características
//	int nFeaturesCuad = 2*nFeatures;
//	// Obtengo la X
//	arma::mat X = arma::mat(trainingSet.size(), nFeaturesCuad+1);
//	for(int i=0; i<trainingSet.size(); i++){
//		for(int j=0; j<nFeatures+1; j++){
//			if(j==0)
//				X(i,j)=1.0;
//			else X(i,j)=trainingSet[i].input[j-1];
//		}
//	}
//	// Elementos cuadráticos
//	for(int i=0; i<trainingSet.size(); i++){
//		for(int j=0; j<nFeatures; j++){
//			X(i,nFeatures+j+1)=pow(trainingSet[i].input[j],2);
//		}
//	}
//	// Obtengo la Y
//	arma::mat y = arma::mat(trainingSet.size(), 1);
//	for(int i=0; i<trainingSet.size(); i++){
//		if(trainingSet[i].burn)
//			y(i)=1;
//		else y(i)=0;
//	}
//	// Calculo la matriz de alpha
//	arma::mat Alpha(nFeaturesCuad+1, nFeaturesCuad+1);
//	Alpha.eye();
//	Alpha(0,0)=0;
//	alphaTrain*Alpha;
////	std::cout << Alpha;
//	// Inicializo theta
//	arma::mat theta = arma::mat(nFeaturesCuad+1, 1);
//	// Calculo vectorialmente
//	theta = arma::pinv(X.t()*X+Alpha)*X.t()*y;
////	std::cout << theta;
//	this->theta.clear();
//	for(int i=0; i<nFeaturesCuad+1; i++){
//		this->theta.push_back(theta(i));
//	}
}

//Pendiente de Sample
void LRMachine::fillX() {
//	for(unsigned int i=0; i<C_trainingSet.size(); i++){
//		for(int j=0; j<C_nFeatures+1; j++){
//			if(j==0)
//				C_X[i][j]=1.0;
//			else C_X[i][j]=C_trainingSet[i].getInput()[j-1];
//		}
//	}
}

//Correcto
void LRMachine::fillTheta() {
	for(int i=0; i<C_nFeatures+1; i++) {
		C_theta.push_back(0.5);
	}
}

//Pendiente de Sample
void LRMachine::fillY() {
	for(unsigned int i=0; i<C_trainingSet.size(); i++){
		C_y[i] = C_trainingSet[i].getResult();
	}
}

void LRMachine::fillActualY(){
	for(unsigned int i=0; i<C_trainingSet.size(); i++){
		C_actualY[i] = C_testingSet[i].getResult();
	}
}
