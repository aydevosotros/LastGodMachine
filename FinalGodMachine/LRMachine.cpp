#include "LRMachine.h"

LRMachine::LRMachine() {
	C_nFeatures = 4;
	C_classifySuccesses = 0;
	iterTrain = 1000;
	alphaTrain = 0.01;
	trainType = 1; //1 normal, 2 gradiente
}

LRMachine::~LRMachine() {}

void LRMachine::setParameters(char *argv[]) {
	std::cout << "I'm setting parameters with the LRMachine" << std::endl;
	C_lambda = atoi(argv[2]);
	std::cout << "Lambda set to " << C_lambda << std::endl;

//	Algo más a partir de argv[3];
}

void LRMachine::addTrainingSet(std::vector<Sample> trainingSet) {
	std::cout << "I'm adding training set with the LRMachine" << std::endl;
	C_trainingSet = trainingSet;
}

void LRMachine::train(){
	std::cout << "I'm training with the LRMachine" << std::endl;
}

//Está copypasteado el classifySample
void LRMachine::predict(Sample input){
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
	for(unsigned int i=0; i<C_trainingSet.size(); i++){
		for(int j=0; j<C_nFeatures+1; j++){
			if(j==0)
				C_X[i][j]=1.0;
			else C_X[i][j]=C_trainingSet[i].input[j-1];
		}
	}
}

//Correcto
void LRMachine::fillTheta() {
	for(int i=0; i<C_nFeatures+1; i++)
		C_theta[i]=0;
}

//Pendiente de Sample
void LRMachine::fillY() {
	for(unsigned int i=0; i<C_trainingSet.size(); i++){
		if(C_trainingSet[i].burn)
			C_y[i]=1;
		else C_y[i]=0;
	}
}
