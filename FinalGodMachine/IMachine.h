#ifndef IMACHINE_H_
#define IMACHINE_H_

#include "Sample.h"

class IMachine {
public:
	virtual void setParameters(char *argv[])=0;
	virtual void addTrainingSet(std::vector<Sample> trainingSet)=0;
	virtual void train()=0;
	virtual void addInput(Sample input)=0;
	virtual void predict()=0;
	virtual void clearTrainingSet()=0;
};

#endif

//	virtual bool isTrainingReady()=0;
//	virtual void classifySample(Sample sample)=0;
//	virtual bool isReadyToCross()=0;
//	virtual bool isDoorOnFire(double input[])=0;
